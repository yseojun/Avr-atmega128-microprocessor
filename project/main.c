#include "USART.h"
#include "SEG_MODULE.h"
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

volatile unsigned int cnt; // 타이머 카운트 변수
volatile unsigned int timer; // 타이머 변수

volatile unsigned int play_game; // 게임 진행 변수
volatile unsigned int level; // 레벨 변수
volatile unsigned int input[10]; // 입력값 저장 배열
volatile unsigned int expect[10]; // 예상값 저장 배열
volatile unsigned int now_input; // 현재 입력값 -> 인터럽트로 받음

void	init_all()
{
	cli(); // 인터럽트 비활성화
	PORTA = 0x00;
	DDRA = 0xFF;
	PORTC = 0x0F;
	DDRC = 0x0F;

	PORTD = 0;
	MCUCR = 0x00;
	EICRB = 0xFF;
	EIMSK = 1 << INT4;

	TCNT0 = 0x00;
	TCCR0 = 1 << CS02 | 1 << CS01;
	TIMSK = 1 << TOIE0;
	cnt = 0;
	timer = 0;
	sei(); // 인터럽트 활성화

	DDRG = 1 << PG0;
}

ISR(TIMER0_OVF_vect) // 타이머 인터럽트
{
	cnt++;
	if (cnt == 100)
	{
		cnt = 0;
		timer++; // 1초마다 타이머 증가
	}
}

ISR(INT4_vect)
{
	seg_disp(timer); // 타이머 출력
}

ISR(INT5_vect)
{
	now_input = 1; // Left 버튼 입력
}

ISR(INT6_vect)
{
	now_input = 2; // Up 버튼 입력
}

ISR(INT7_vect)
{	
	now_input = 3; // Right 버튼 입력
}

void	chk_level() // do_level 내부 입력 체크 함수
{
	int	idx = 0;
	while (idx < level) // 레벨만큼 idx 증가, 입력값과 예상값 비교
	{
		if (input[idx] != expect[idx]) // 일치하지 않으면 게임 종료
		{
			tx_string("Fail\n");
			_delay_ms(1000);
			play_game = 0;
			level = 1;
			EIMSK = 1 << INT4; // 인터럽트 비활성화
			return ; // 함수 종료
		}
		idx++;
	}
	level++; // 레벨 증가
	if (level == 10) // 레벨 10 클리어시 게임 종료
	{
		tx_string("You Win!!!\n");
		play_game = 0;
		level = 1;
		EIMSK = 1 << INT4; // 인터럽트 비활성화
	}
	else
		tx_string("Level Done!!!\n");
	PORTG = 1 << PG0; // 승리시 LED on
	_delay_ms(1000);
	PORTG = 0; // LED  off
}

void	do_level()
{
	tx_string("Remember !!\n");
	int	random;

	int idx = 0;
	while (idx < level)
	{
		random = rand() % 3 + 1; // 1~3 랜덤값 생성
		if (random == 1)
			tx_string("Left!!!\n");
		else if (random == 2)
			tx_string("Up!!\n");
		else if (random == 3)
			tx_string("Right!\n");
		expect[idx] = random; // 예상값 저장
		idx++;
		_delay_ms(1000);
	}

	tx_string("Remember!!\n");
	_delay_ms(3000);
	for (int i = 0; i < 20; i++)
		tx_string("\n");
	tx_string("Start Game!!\n");
	tx_string("Taking input...\n");

	idx = 0;
	while (idx < level)
	{
		now_input = 0; // 입력값 초기화
		while (now_input == 0); // 입력값이 들어올때까지 대기 -> 인터럽트로 입력값 받음
		if (now_input == 1)
			tx_string("Left\n");
		else if (now_input == 2)
			tx_string("Up\n");
		else if (now_input == 3)
			tx_string("Right\n");
		input[idx] = now_input; // 입력값 저장
		idx++;
	}
	chk_level(); // 입력값 체크
}

int main(void)
{
	init_all(); // 입출력, 인터럽트, 타이머 초기화
	usart_init(BAUD_9600); // USART 초기화
	play_game = 0; // 게임 시작 변수 초기화
	level = 1; // 레벨 변수 초기화
	while (1)
	{
		if (play_game == 1) // 게임 진행 O
		{
			if (level == 1) // 게임 시작시 안내
			{
				tx_string("Left : 5, Up : 6, Right : 7\n");
				tx_string("Remember script, and press in order!\n");
				_delay_ms(5000);
			}
			do_level(); // 게임 레벨 진행, 레벨 클리어시 다음 레벨 진행
		}
		else // 게임 진행 X
		{
			while (play_game == 0) // 게임 시작 대기
			{
				tx_string("Press PG3 to start GAME!\n");
				if (PING & (1 << PG3)) // PG3 버튼 누르면 게임 시작
				{
					EIMSK = 1 << INT7 | 1 << INT6 | 1 << INT5 | 1 << INT4; // 게임 키 인터럽트 활성화
					play_game = 1; // 게임 시작 변수 활성화
				}
				_delay_ms(1000);
			}
		}
		_delay_ms(100);
	}
}
