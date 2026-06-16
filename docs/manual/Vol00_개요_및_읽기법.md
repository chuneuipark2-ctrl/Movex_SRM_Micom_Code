# Vol.00 — 개요 및 코드 읽기법

> 생성일: 2026-06-16

## 목적

이름·플래그·문구의 **실제 용도** 참조 사전. C 문법 교재 아님.

| 항목 | 설명 |
|------|------|
| 원문 주석 | 헤더 인라인 주석 |
| 용도 | 이름과 다를 수 있는 실제 역할 |
| 코드 참조 | 자동 grep 최대 5건 |

## 1. 시스템 요약

- MCU: STM32F767, 3축 SRM (주행/승강/포크)
- 통신: TML UART Vexi (`com_tml.c`)
- 상태머신: `SRM_Machine_Run_Process()` / `enumSRM_RUN_SEQ`
- 작업: `0x41` → `m_WorkData` / `0x50` Start → `RUN_SEQ_START`
- 상태보고: `0x30` → `m_St`

## 2. 전역 변수

| 심볼 | 용도 |
|------|------|
| m_St | 지상반 운전상태 |
| m_pgmEnv | 파라미터 |
| m_WorkData | 작업 큐 |
| m_ExtSEnv0~2 | 축 환경 |
| m_BKSram | BKPSRAM 미러 |

## 3. 명명 함정 TOP5

1. **GoodsFlag_Or_MoveHome** — 축마다 의미 다름
2. **Rack_fork_obstruction** — 센서≠WCS 스킵금지 플래그
3. **Save_* vs Store_*** — 폴링상태 vs 큐적재
4. **SRM_TaskMode** — 0x40 전용
5. **RETURN_HOME vs HOME** — 에러복귀 vs 원점

## 4. grep 4단계

1. 심볼 검색 2. =1 세팅처 3. if 블록 4. RunMode/Save 호출

## 5. 파일 맵

| 파일 | 역할 |
|------|------|
| dev_SRM.c | 상태머신 |
| com_tml.c | TML |
| alarm.c | Save_* |
| User_Define.h | 구조체 |
| dev_SRM.h | RunMode |
| error_code.h | ERROR1 |

---

## 부록 0.1 — 현장 디버깅 체크 (1)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.2 — 현장 디버깅 체크 (2)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.3 — 현장 디버깅 체크 (3)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.4 — 현장 디버깅 체크 (4)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.5 — 현장 디버깅 체크 (5)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.6 — 현장 디버깅 체크 (6)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.7 — 현장 디버깅 체크 (7)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.8 — 현장 디버깅 체크 (8)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.9 — 현장 디버깅 체크 (9)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.10 — 현장 디버깅 체크 (10)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.11 — 현장 디버깅 체크 (11)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.12 — 현장 디버깅 체크 (12)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.13 — 현장 디버깅 체크 (13)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.14 — 현장 디버깅 체크 (14)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.15 — 현장 디버깅 체크 (15)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.16 — 현장 디버깅 체크 (16)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.17 — 현장 디버깅 체크 (17)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.18 — 현장 디버깅 체크 (18)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.19 — 현장 디버깅 체크 (19)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.20 — 현장 디버깅 체크 (20)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.21 — 현장 디버깅 체크 (21)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.22 — 현장 디버깅 체크 (22)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.23 — 현장 디버깅 체크 (23)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.24 — 현장 디버깅 체크 (24)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.25 — 현장 디버깅 체크 (25)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.26 — 현장 디버깅 체크 (26)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.27 — 현장 디버깅 체크 (27)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.28 — 현장 디버깅 체크 (28)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.29 — 현장 디버깅 체크 (29)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.30 — 현장 디버깅 체크 (30)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.31 — 현장 디버깅 체크 (31)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.32 — 현장 디버깅 체크 (32)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.33 — 현장 디버깅 체크 (33)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.34 — 현장 디버깅 체크 (34)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.35 — 현장 디버깅 체크 (35)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.36 — 현장 디버깅 체크 (36)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.37 — 현장 디버깅 체크 (37)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.38 — 현장 디버깅 체크 (38)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.39 — 현장 디버깅 체크 (39)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.40 — 현장 디버깅 체크 (40)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.41 — 현장 디버깅 체크 (41)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.42 — 현장 디버깅 체크 (42)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.43 — 현장 디버깅 체크 (43)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.44 — 현장 디버깅 체크 (44)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

## 부록 0.45 — 현장 디버깅 체크 (45)

1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM

