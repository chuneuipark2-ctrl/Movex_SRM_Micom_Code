

#include "main.h"
#include "type.h"
#include "User_Define.h"
#include "uart.h"
#include "rtc.h"
#include "dev_SRM.h"
#include "upgrade.h"

extern RTC_HandleTypeDef hrtc;

extern PGMEnvSTR m_pgmEnv;

extern HMI_Com		m_HMI_Com;

//=============================================================================
// UTC Offset 정의 (초 단위)
// 양수: UTC 동쪽 (로컬 → UTC 변환 시 빼기)
// 음수: UTC 서쪽 (로컬 → UTC 변환 시 더하기)
//=============================================================================

//-----------------------------------------------------------------------------
// 아시아
//-----------------------------------------------------------------------------
#define TZ_OFFSET_KST       ( 32400)  // UTC+9:00  한국 표준시 (Korea Standard Time)
#define TZ_OFFSET_JST       ( 32400)  // UTC+9:00  일본 표준시 (Japan Standard Time)
#define TZ_OFFSET_CST_CN    ( 28800)  // UTC+8:00  중국 표준시 (China Standard Time)
#define TZ_OFFSET_SGT       ( 28800)  // UTC+8:00  싱가포르   (Singapore Time)
#define TZ_OFFSET_ICT       ( 25200)  // UTC+7:00  인도차이나  (Indochina Time)
#define TZ_OFFSET_WIB       ( 25200)  // UTC+7:00  서인도네시아 (Western Indonesia Time)
#define TZ_OFFSET_IST       ( 19800)  // UTC+5:30  인도 표준시 (India Standard Time)
#define TZ_OFFSET_PKT       ( 18000)  // UTC+5:00  파키스탄   (Pakistan Standard Time)

//-----------------------------------------------------------------------------
// 유럽
//-----------------------------------------------------------------------------
#define TZ_OFFSET_GMT       (     0)  // UTC+0:00  그리니치   (Greenwich Mean Time)
#define TZ_OFFSET_WET       (     0)  // UTC+0:00  서유럽     (Western European Time)
#define TZ_OFFSET_WEST      (  3600)  // UTC+1:00  서유럽 썸머 (Western European Summer Time)
#define TZ_OFFSET_CET       (  3600)  // UTC+1:00  중앙유럽   (Central European Time)
#define TZ_OFFSET_CEST      (  7200)  // UTC+2:00  중앙유럽 썸머 (Central European Summer Time)
#define TZ_OFFSET_EET       (  7200)  // UTC+2:00  동유럽     (Eastern European Time)
#define TZ_OFFSET_EEST      ( 10800)  // UTC+3:00  동유럽 썸머 (Eastern European Summer Time)
#define TZ_OFFSET_MSK       ( 10800)  // UTC+3:00  모스크바   (Moscow Standard Time)

//-----------------------------------------------------------------------------
// 미주
//-----------------------------------------------------------------------------
#define TZ_OFFSET_EST       (-18000)  // UTC-5:00  미국 동부 표준시 (Eastern Standard Time)
#define TZ_OFFSET_EDT       (-14400)  // UTC-4:00  미국 동부 썸머타임 (Eastern Daylight Time)
#define TZ_OFFSET_CST       (-21600)  // UTC-6:00  미국 중부 표준시 (Central Standard Time)
#define TZ_OFFSET_CDT       (-18000)  // UTC-5:00  미국 중부 썸머타임 (Central Daylight Time)
#define TZ_OFFSET_MST       (-25200)  // UTC-7:00  미국 산악 표준시 (Mountain Standard Time)
#define TZ_OFFSET_MDT       (-21600)  // UTC-6:00  미국 산악 썸머타임 (Mountain Daylight Time)
#define TZ_OFFSET_PST       (-28800)  // UTC-8:00  미국 태평양 표준시 (Pacific Standard Time)
#define TZ_OFFSET_PDT       (-25200)  // UTC-7:00  미국 태평양 썸머타임 (Pacific Daylight Time)
#define TZ_OFFSET_AKT       (-32400)  // UTC-9:00  알래스카 표준시 (Alaska Standard Time)
#define TZ_OFFSET_AKDT      (-28800)  // UTC-8:00  알래스카 썸머타임 (Alaska Daylight Time)
#define TZ_OFFSET_HST       (-36000)  // UTC-10:00 하와이   (Hawaii Standard Time)
#define TZ_OFFSET_BRT       (-10800)  // UTC-3:00  브라질   (Brasilia Time)
#define TZ_OFFSET_ART       (-10800)  // UTC-3:00  아르헨티나 (Argentina Time)

//-----------------------------------------------------------------------------
// 오세아니아
//-----------------------------------------------------------------------------
#define TZ_OFFSET_AEST      ( 36000)  // UTC+10:00 호주 동부 표준시 (Australian Eastern Standard Time)
#define TZ_OFFSET_AEDT      ( 39600)  // UTC+11:00 호주 동부 썸머타임 (Australian Eastern Daylight Time)
#define TZ_OFFSET_NZST      ( 43200)  // UTC+12:00 뉴질랜드 표준시 (New Zealand Standard Time)
#define TZ_OFFSET_NZDT      ( 46800)  // UTC+13:00 뉴질랜드 썸머타임 (New Zealand Daylight Time)

//-----------------------------------------------------------------------------
// 중동 / 아프리카
//-----------------------------------------------------------------------------
#define TZ_OFFSET_AST       ( 10800)  // UTC+3:00  아랍 표준시  (Arabia Standard Time)
#define TZ_OFFSET_GST       ( 14400)  // UTC+4:00  걸프 표준시  (Gulf Standard Time)
#define TZ_OFFSET_IRST      ( 12600)  // UTC+3:30  이란 표준시  (Iran Standard Time)
#define TZ_OFFSET_EAT       ( 10800)  // UTC+3:00  동아프리카   (East Africa Time)
#define TZ_OFFSET_CAT       (  7200)  // UTC+2:00  중앙아프리카 (Central Africa Time)
#define TZ_OFFSET_WAT       (  3600)  // UTC+1:00  서아프리카   (West Africa Time)

INT32U getDoW(INT32U y, INT32U m, INT32U d)
{
	// Zeller's formula: 0=Sunday
	if (m < 3) { m += 12; y -= 1; }
	return (d + (13 * (m + 1) / 5) + y + y / 4 - y / 100 + y / 400 + 6) % 7;
}

/**
 * @brief  Converts Unix timestamp to UTC time structure
 * @param  nUnixTime: Total seconds since Jan 1, 1970
 * @return struct tm: Populated UTC time structure
 */
struct tm Convert_Unix_To_Tm(uint32_t nUnixTime) 
{
	struct tm utc_struct;
	INT32U days, seconds_in_day;
	INT32U yday = 0;
	int year = 1970;

	/* 월별 일수 (평년 기준) */
	static const int days_in_month[] = {
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};

	/* 1. 시각 계산 */
	seconds_in_day = nUnixTime % 86400U;
	utc_struct.tm_hour = (int)(seconds_in_day / 3600U);
	utc_struct.tm_min = (int)((seconds_in_day % 3600U) / 60U);
	utc_struct.tm_sec = (int)(seconds_in_day % 60U);

	/* 2. Epoch 이후 총 일수 */
	days = nUnixTime / 86400U;

	/* 3. 연도 계산 */
	while (1)
	{
		int leap = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
		INT32U days_in_year = leap ? 366U : 365U;

		if (days < days_in_year) break;

		days -= days_in_year;
		year++;
	}
	utc_struct.tm_year = year - 1900;

	/* 4. 월 및 일 계산 */
	{
		int leap = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
		int month = 0;

		for (month = 0; month < 12; month++)
		{
			int dim = days_in_month[month];
			if (month == 1 && leap) dim = 29;  /* 2월 윤년 보정 */

			if (days < (INT32U)dim) break;

			yday += (INT32U)dim;
			days -= (INT32U)dim;
		}
		utc_struct.tm_mon = month;
		utc_struct.tm_mday = (int)days + 1;
		yday += days;
	}

	/* 5. 연중 일수 (0-indexed, 0=1월 1일) */
	utc_struct.tm_yday = (int)yday;

	/* 6. 요일 계산 (0=일요일)
	 *    [수정] 기존에 tm_wday 미계산으로 RTC WeekDay에 쓰레기값이 저장되던 버그 수정 */
	utc_struct.tm_wday = (int)getDoW(
		(INT32U)year,
		(INT32U)(utc_struct.tm_mon + 1),
		(INT32U)utc_struct.tm_mday
	);

	/* 7. UTC는 DST 미적용 */
	utc_struct.tm_isdst = 0;

	return utc_struct;
}

/**
 * @brief  struct tm → Unix 타임스탬프 변환 (UTC 기준)
 * @note   [수정] 함수명 변경: Convert_Unix_To_Utc → Convert_Tm_To_Unix
 *                (기존 이름은 동작과 반대 방향이었음)
 *         [수정] 윤년 누적 계산을 명시적 루프 방식으로 교체
 *                기존 근사 공식((year-1969)/4 - (year-1901)/100 ...)은
 *                2100년(윤년 아님)을 윤년으로 오계산하는 버그 있음
 * @param  utc: UTC 시각 구조체 (const 포인터)
 * @return Unix 타임스탬프 (초)
 */
uint32_t Convert_Tm_To_Unix(struct tm* utc) 
{
	INT32U total_days = 0;
	INT32U y;
	int year = utc->tm_year + 1900;
	int mon = utc->tm_mon;     /* 0-indexed */
	int day = utc->tm_mday;
	int hour = utc->tm_hour;
	int min = utc->tm_min;
	int sec = utc->tm_sec;

	/* 월별 누적 일수 (평년, 0-indexed 월 기준) */
	static const int days_before_month[] = {
		0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
	};

	/* 1. 1970 ~ (year-1) 까지 일수 누산
	 *    [수정] 근사 공식 → 명시적 루프로 교체하여 2100년 등 버그 제거 */
	for (y = 1970U; y < (INT32U)year; y++)
	{
		int leap = ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0));
		total_days += leap ? 366U : 365U;
	}

	/* 2. 해당 연도의 월 이전 일수 */
	total_days += (INT32U)days_before_month[mon];

	/* 3. 윤년이고 3월 이후(mon >= 2)면 하루 추가 */
	{
		int leap = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
		if (mon >= 2 && leap) total_days += 1U;
	}

	/* 4. 해당 월의 경과 일수 (day는 1-indexed) */
	total_days += (INT32U)(day - 1);

	/* 5. 초 단위로 변환 */
	return total_days * 86400U
		+ (INT32U)hour * 3600U
		+ (INT32U)min * 60U
		+ (INT32U)sec;
}

INT08U isDaylightSavingTime(INT32U year, INT32U month, INT32U day, INT32U hour)
{
	INT32U dow, secondSunday, firstSunday;

	if (month < 3 || month > 11) return 0;  // 1~2월, 12월: 표준시
	if (month > 3 && month < 11) return 1;  // 4~10월: 항상 섬머타임

	if (month == 3)
	{
		// 3월 둘째 주 일요일 계산
		dow = getDoW(year, 3, 1);           // 3월 1일 요일
		secondSunday = (7 - dow) % 7 + 8;  // 둘째 일요일 날짜
		if (day > secondSunday) return 1;
		if (day < secondSunday) return 0;
		return (hour >= 2) ? 1 : 0;         // 당일 02:00 이후부터 적용
	}

	if (month == 11)
	{
		// 11월 첫째 주 일요일 계산
		dow = getDoW(year, 11, 1);          // 11월 1일 요일
		firstSunday = (7 - dow) % 7 + 1;   // 첫째 일요일 날짜
		if (day > firstSunday) return 0;
		if (day < firstSunday) return 1;
		return (hour >= 2) ? 0 : 1;         // 당일 02:00 이후부터 표준시
	}

	return 0;
}

INT08U isDaylightSavingTime_Utc(INT32U nUtcTime)
{
	struct tm utc_struct;
	INT32U dow = 0, secondSunday = 0, firstSunday = 0;

	int year = 0, month = 0, day = 0, hour = 0;

	utc_struct = Convert_Unix_To_Tm(nUtcTime);

	// struct tm: jan=0, feb=1, mar=2, apr=3, ... oct=9, nov=10, dec=11
	month = utc_struct.tm_mon;
	day = utc_struct.tm_mday;
	hour = utc_struct.tm_hour;
	year = utc_struct.tm_year + 1900;

	// 1. Off-season: Jan(0), Feb(1), Dec(11)
	if (month < 2 || month > 10) return 0;

	// 2. DST-season: Apr(3) ~ Oct(9)
	if (month > 2 && month < 10) return 1;

	// 3. March (Index 2): Second Sunday at 02:00
	if (month == 2)
	{
		dow = getDoW(year, 3, 1); // Get day of week for March 1st
		secondSunday = (7 - dow) % 7 + 8;

		if (day > secondSunday) return 1;
		if (day < secondSunday) return 0;
		return (hour >= 2) ? 1 : 0;
	}

	// 4. November (Index 10): First Sunday at 02:00
	if (month == 10)
	{
		dow = getDoW(year, 11, 1); // Get day of week for Nov 1st
		firstSunday = (7 - dow) % 7 + 1;

		if (day > firstSunday) return 0;
		if (day < firstSunday) return 1;
		return (hour >= 2) ? 0 : 1;
	}

	return 0;
}

/**
  * @brief  RTC에 UTC 시각을 설정
  * @note   [수정] 파라미터 INT32S → INT32U (UTC 타임스탬프는 부호 없는 타입으로 통일)
  *         [수정] Convert_Unix_To_Tm 함수명 변경 반영
  *         [수정] HAL_RTC_SetDate/SetTime 반환값 확인 추가 (기존과 동일하나 명시)
  * @param  nUtcTime: UTC Unix 타임스탬프
  * @retval none
  */
void setTimeDate_Rev2(INT32U nUtcTime)
{
	RTC_DateTypeDef nDate;
	RTC_TimeTypeDef nTime;
	struct tm Utc_Struct;

	if (checkFusingString((INT08U*)m_ExtSEnv.mDevice.ProjectID.ProjectNo, (INT08U*)HANKOOK_TIRE_TP2, 6) == 0)
	{
		// 미국 중부 시간 보정 (UTC → 로컬: nLocalTime = nUtcTime + TZ_OFFSET_xxx)
		if (isDaylightSavingTime_Utc(nUtcTime))
		{
			nUtcTime = (INT32U)((INT32S)nUtcTime + TZ_OFFSET_CDT);  // CDT (UTC-5)
		}
		else
		{
			nUtcTime = (INT32U)((INT32S)nUtcTime + TZ_OFFSET_CST);  // CST (UTC-6)
		}
	}
	else
	{
		// 한국 시간 보정 (UTC → KST: nKstTime = nUtcTime + TZ_OFFSET_KST)
		nUtcTime += TZ_OFFSET_KST;
	}

	Utc_Struct = Convert_Unix_To_Tm(nUtcTime);

	nDate.Year = RTC_ByteToBcd2((INT08U)(Utc_Struct.tm_year - 100));
	nDate.Month = RTC_ByteToBcd2((INT08U)(Utc_Struct.tm_mon + 1));
	nDate.Date = RTC_ByteToBcd2((INT08U)Utc_Struct.tm_mday);

	/* [수정] tm_wday는 Convert_Unix_To_Tm 내부에서 정상 계산됨
	 *        RTC HAL WeekDay 매핑:
	 *          tm_wday  0(일) → RTC_WEEKDAY_SUNDAY (7)
	 *          tm_wday  1(월) → 1, ..., 6(토) → 6  */
	nDate.WeekDay = (Utc_Struct.tm_wday == 0) ? RTC_WEEKDAY_SUNDAY
		: (INT08U)Utc_Struct.tm_wday;

	if (HAL_RTC_SetDate(&hrtc, &nDate, RTC_FORMAT_BCD) != HAL_OK)
	{
		Error_Handler();
	}

	nTime.Hours = RTC_ByteToBcd2((INT08U)Utc_Struct.tm_hour);
	nTime.Minutes = RTC_ByteToBcd2((INT08U)Utc_Struct.tm_min);
	nTime.Seconds = RTC_ByteToBcd2((INT08U)Utc_Struct.tm_sec);
	nTime.TimeFormat = RTC_HOURFORMAT12_AM;
	nTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	nTime.StoreOperation = RTC_STOREOPERATION_RESET;

	if (HAL_RTC_SetTime(&hrtc, &nTime, RTC_FORMAT_BCD) != HAL_OK)
	{
		Error_Handler();
	}

#if DEBUG_RTC
	printf("[RTC]SetTimeDate %d/%d/%d %d:%d:%d \r\n",
		get_bcd2dec(nDate.Year), get_bcd2dec(nDate.Month), get_bcd2dec(nDate.Date),
		get_bcd2dec(nTime.Hours), get_bcd2dec(nTime.Minutes), get_bcd2dec(nTime.Seconds));
#endif
}

/**
  * @brief  RTC에서 UTC 시각을 읽어 Unix 타임스탬프로 반환
  * @note   [수정] HAL_RTC_GetTime/GetDate 반환값 오류 처리 추가
  *                오류 시 0을 반환하므로 호출부에서 0 여부 확인 필요
  *         [수정] Set_HMI_SysTime_* 에 BCD 원시값 대신 십진수로 저장
  *                (기존: BCD 원시값 → HMI에서 숫자 오해석 위험)
  *         [수정] Convert_Tm_To_Unix 함수명 변경 반영
  * @retval UTC Unix 타임스탬프, HAL 오류 시 0
  */
INT32U getTimeDate_Rev2(void)
{
	RTC_DateTypeDef nDate;
	RTC_TimeTypeDef nTime;
	struct tm utc_struct;
	INT32U time = 0;

	/* STM32 HAL 주의: GetTime() 후 반드시 GetDate() 호출해야
	 * 내부 섀도 레지스터 잠금이 해제됩니다. 순서 변경 금지. */
	if (HAL_RTC_GetTime(&hrtc, &nTime, RTC_FORMAT_BCD) != HAL_OK)
	{
		return 0;
	}
	if (HAL_RTC_GetDate(&hrtc, &nDate, RTC_FORMAT_BCD) != HAL_OK)
	{
		return 0;
	}

	/* BCD → 십진수 변환 후 struct tm 매핑 */
	utc_struct.tm_sec = RTC_Bcd2ToByte(nTime.Seconds);
	utc_struct.tm_min = RTC_Bcd2ToByte(nTime.Minutes);
	utc_struct.tm_hour = RTC_Bcd2ToByte(nTime.Hours);
	utc_struct.tm_mday = RTC_Bcd2ToByte(nDate.Date);
	utc_struct.tm_mon = RTC_Bcd2ToByte(nDate.Month) - 1;  /* 0-indexed */
	utc_struct.tm_year = RTC_Bcd2ToByte(nDate.Year) + 100; /* RTC 24 → tm 124 (=2024) */
	utc_struct.tm_isdst = -1;

	memcpy(&m_pgmEnv.SysTime, &utc_struct, sizeof(struct tm));

	/* [수정] BCD 원시값 → 십진수 변환 후 저장
	 *        HMI에서 get_bcd2dec() 없이 바로 숫자로 사용 가능 */
	m_pgmEnv.Set_HMI_SysTime_Year = RTC_Bcd2ToByte(nDate.Year);
	m_pgmEnv.Set_HMI_SysTime_Mon = RTC_Bcd2ToByte(nDate.Month);
	m_pgmEnv.Set_HMI_SysTime_Day = RTC_Bcd2ToByte(nDate.Date);
	m_pgmEnv.Set_HMI_SysTime_Hour = RTC_Bcd2ToByte(nTime.Hours);
	m_pgmEnv.Set_HMI_SysTime_Min = RTC_Bcd2ToByte(nTime.Minutes);

#if DEBUG_RTC
	printf("[RTC]GetTimeDate %d/%d/%d %d:%d:%d \r\n",
		RTC_Bcd2ToByte(nDate.Year), RTC_Bcd2ToByte(nDate.Month), RTC_Bcd2ToByte(nDate.Date),
		RTC_Bcd2ToByte(nTime.Hours), RTC_Bcd2ToByte(nTime.Minutes), RTC_Bcd2ToByte(nTime.Seconds));
#endif

	time = Convert_Tm_To_Unix(&utc_struct);

	if (checkFusingString((INT08U*)m_ExtSEnv.mDevice.ProjectID.ProjectNo, (INT08U*)HANKOOK_TIRE_TP2, 6) == 0)
	{
		/* 미국 중부 로컬 → UTC 역변환
		 * [수정] isDaylightSavingTime_US() 사용: 로컬 struct tm이 이미 있으므로
		 *        UTC 기준 함수(isDaylightSavingTime_Utc)를 쓰면 이중 변환 오류 발생 */
		INT32U local_year = (INT32U)(utc_struct.tm_year + 1900);
		INT32U local_month = (INT32U)(utc_struct.tm_mon + 1);
		INT32U local_day = (INT32U)utc_struct.tm_mday;
		INT32U local_hour = (INT32U)utc_struct.tm_hour;

		if (isDaylightSavingTime(local_year, local_month, local_day, local_hour))
		{
			time = (INT32U)((INT32S)time - TZ_OFFSET_CDT);  // 로컬 CDT → UTC
		}
		else
		{
			time = (INT32U)((INT32S)time - TZ_OFFSET_CST);  // 로컬 CST → UTC
		}
	
	}
	else
	{
		// 한국 시간 보정 (KST → UTC: nKstTime = time - TZ_OFFSET_KST)
		time -= TZ_OFFSET_KST;
	}

	return time;
}


/**
  * @brief
  * @param  none
  * @retval none
  */
void loadBKSramSTR(void)
{
#if DEBUG_BACKUPSRAM
	printf("[DEBUG_APP] load BackUp Sram Addr:%lx Size:%d\n\r", \
		BKPSRAM_BASE, sizeof(BKSRamSTR));
#endif

	memcpy((INT08U*)&m_BKSram, (INT08U*)(BKPSRAM_BASE), sizeof(BKSRamSTR));
}

/**
  * @brief
  * @param  none
  * @retval none
  */
void saveBKSramSTR(void)
{
	//m_BKSram.ParaCRC = calcParameterCrc(0);
	//m_TestStatus.Ctrl[DEBUG_BUFFER_11] = m_BKSram.ParaCRC;
#if DEBUG_BACKUPSRAM
	printf("[DEBUG_APP] Save BackUp Sram Addr:%lx Size:%d\n\r", \
		BKPSRAM_BASE, sizeof(BKSRamSTR));
#endif
	memcpy((INT08U*)(BKPSRAM_BASE), (INT08U*)&m_BKSram, sizeof(BKSRamSTR));
}

/**
  * @brief
  * @param  none
  * @retval none
  */
INT16U loadBKSramBlock(INT08U* ptr, INT16U len)
{
	INT16U ret = 0;
	INT32U addr = 0;
	INT32U offset = 0;
	INT32U base_addr = 0;
	INT32U data_addr = 0;

	base_addr = (INT32U)&m_BKSram;
	data_addr = (INT32U)ptr;

	if (data_addr >= base_addr)
	{
		offset = data_addr - base_addr;
		if ((offset + len) < 4095)
		{
			addr = BKPSRAM_BASE + offset;

			memcpy((INT08U*)ptr, (INT08U*)(addr), len);

			ret = len;
		}
	}

#if DEBUG_BACKUPSRAM
	printf("[DEBUG_APP] Load BackUp Sram Addr:%lx Size:%d\n\r", \
		addr, len);
#endif

	return ret;
}

/**
  * @brief
  * @param  none
  * @retval none
  */
INT16U saveBKSramBlock(INT08U* ptr, INT16U len)
{
	INT16U ret = 0;
	INT32U addr = 0;
	INT32U offset = 0;
	INT32U base_addr = 0;
	INT32U data_addr = 0;

	base_addr = (INT32U)&m_BKSram;
	data_addr = (INT32U)ptr;

	if (data_addr >= base_addr)
	{
		offset = data_addr - base_addr;
		//if ((offset + len) < 4095)
		if ((offset + len) < 4096)
		{
			addr = BKPSRAM_BASE + offset;

			memcpy((INT08U*)(addr), (INT08U*)ptr, len);
			ret = len;
		}
	}

#if DEBUG_BACKUPSRAM
	printf("[DEBUG_APP] Save BackUp SRAM Address : 0x%lx Size:%d\n\r", \
		addr, len);
#endif

	return ret;
}

