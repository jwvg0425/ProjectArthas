#Robotopia  

##5주차 업데이트 노트  
week5 폴더안에 바로 실행 가능한 Release 파일이 있습니다  

###주의###
빌드 하기전에 프로젝트 - 속성 - 디버깅 - 작업 디렉토리를 $(ProjectDir)../Resources로 바꿔주세요. 그래야 게임 실행 도중 터지는 불상사가 발생하지 않습니다. 

###조작###
WASD - 이동  
SPACE - 점프(S + 점프 -> 특정 블록(floor)위에서는 다운 점프 가능)  
1,2,3 - 기어 변환. 3번 기어 상태일 때는 날 수 있음.

###맵 생성 알고리즘 안정화  
- room config data 추가  
- 층이동 추가  
- 마을 생성  
  
###맵 흔들기 기능 추가  
- 맵 흔들면 현재 방 제외하고 모두 리셋  
  
###캐릭터 스프라이트 추가  
- 파츠 별 렌더  
- 상하체 분리  
  
###장비 아이템 만들기  
- 7가지 종류 장비 아이템(Head, Engine, Armor, Melee Weapon, Range Weapon, Steam Container, Leg)  
  
###Robot Assembly Scene 추가  
- DataManager에서 장비 Data 받아와서 장비 나열  
- 마우스 휠로 장비리스트 스크롤  
- Icon Lock / Unlock 구분  
- 장비 선택 가능  
- 장비 속성 라벨 작업(수정 중)  
  
###버튼 Layer 콜백 함수 추가  
  
###버그픽스
- 플로어 위아래 뒤바뀌는 버그 수정  
- 시작 시 비정상종료 버그 수정  
- 마우스 조작 버그 수정  
