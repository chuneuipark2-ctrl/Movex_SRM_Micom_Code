# SRM 코드 이해 문서

## 어떤 파일을 쓸까?

| 목적 | 파일 |
|------|------|
| **전체 코드 체계적 이해 (먼저 읽기)** | **SRM_전체코드_학습가이드_20260616.html** |
| 심볼 이름·용도 검색 (Ctrl+F) | SRM_전체심볼_용도사전.html |
| 구조체 트리만 가볍게 | SRM_구조체트리.html |

- **학습 가이드** = 흐름·패턴·4주 로드맵·상태머신 지도
- **심볼 사전** = 7,770항목 찾기용 (학습 가이드와 병행)

## 학습 가이드 포함 내용
- 시스템 4층 아키텍처, main 루프, 데이터 3층
- TML 0x30/0x41/0x50 흐름
- RunMode 그룹별 전체 표 + Mermaid 상태전이도
- GET/PUT 사이클, PREPARE_MOVE·브레이크 해제 상세
- 코딩 패턴 6종, 명명 함정 8선, 연습문제
- 타 설비 이식 체크리스트, 새 step 설계법

## 심볼 사전 (완전판)
- 구조체 타입 242개 전체 트리 + 전역/static + 함수/enum/define 7770항목
- 섹션0: 파일 색인, 전역 변수, 핵심 8대 구조체

## PDF 저장
Chrome/Edge → 해당 HTML → 인쇄 → PDF

## 재생성
```bash
node docs/manual/generate_learning_guide.js
node docs/manual/generate_full_manual.js
```

생성: 2026-06-16
