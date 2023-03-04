#include <stdio.h>
#include<stdlib.h>
#define FRAME 10 
#define BALL 21

void get_pnumber();
void get_score(int player, int *rank);
void ten_frame(int a, int best, int **score, int **p);
void calculation(int player, int a, int b, int **score, int **p, int *rank);
void strike(int a, int b, int i, int **sum, int **score, int **p);
void spare(int a, int b, int i, int **sum, int **score, int **p);
void stack(int a, int b, int **sum, int **p);
void result_chart(int a, int **sum, int **score);
void strike_times(int best);
void total_rank(int player, int *rank);
void bubble(int *i, int *j);

int main()
{
	get_pnumber();

	return 0;
}

void get_pnumber()
{
	int a, i = 0, player;
	int *rank = NULL;

	printf("----------------------------------------------------------------------------------\n");
	printf("                                 볼링 게임 start                                  \n");
	printf("----------------------------------------------------------------------------------\n");

	while (i < 1)
	{
		printf("플레이 할 인원 수를 입력하시오(최대 4명) : ");
		scanf("%d", &player);

		if (player > 4)
		{
			printf("플레이 인원수가 4명을 초과하였습니다.\n\n");
			continue;
		}

		i++;
	}

	printf("\n");

	rank = (int *)malloc(player * sizeof(int));

	switch (player)
	{
	case 1:
		for (a = 0; a < 1; a++)
		{
			get_score(player, rank);
			printf("당신의 점수는 %d점입니다.\n", rank[a]);
			break;

		}break;

	case 2:
		for (a = 0; a < 2; a++)
		{
			get_score(player, rank);
			break;
		}break;

	case 3:
		for (a = 0; a < 3; a++)
		{
			get_score(player, rank);
			break;
		}break;

	default:
		for (a = 0; a < 4; a++)
		{
			get_score(player, rank);
			break;
		}break;
	}
}

void get_score(int player, int *rank)
{
	int a, b, i; // a= 선수 수, b= 프레임 수, i = 루프 제어 변수
	int **p;
	int **score; // 점수 받음
	int best = 0; // 스트라이크 누적 횟수 계산

	p = (int**)malloc((player + 2) * sizeof(int*));
	for (b = 0; b < (player + 2); b++)
	{
		p[b] = (int *)malloc((FRAME + 2) * sizeof(int));
	}

	score = (int**)malloc((player + 2) * sizeof(int*));
	for (b = 0; b < (player + 2); b++)
	{
		score[b] = (int *)malloc((BALL + 2) * sizeof(int));
	}

	for (a = 0; a < player; a++)
	{
		for (b = 0; b < FRAME; b++)
		{
			printf("%d번 PLAYER \n", a + 1);

			if (b < 9)
			{
				for (i = 0; i < 18; i++)
				{
					printf("%d frame \n", b + 1);
					printf("1st score: ");
					scanf("%d", &score[a][i]);

					if (score[a][i] == 10)
					{
						score[a][i + 1] = 0;
						best++;
						printf("2nd score : - \n");
						strike_times(best);
					}

					else // 그렇지 않으면
					{
						printf("2nd score: ");
						scanf("%d", &score[a][i + 1]);
						best = 0;
					}

					printf("\n");

					p[a][b] = score[a][i] + score[a][i + 1];

					if (p[a][b] > 10)
					{
						printf("\n입력한 점수의 합이 10보다 큽니다.\n\n");
						i--;
						continue;
					}
					b++;
					i++;
				}

			}

			if (b == 9) // 10번 프레임이면
			{
				ten_frame(a, best, score, p);
			}
		}
		best = 0;
	}
	calculation(player, a, b, score, p, rank);

	for (b = 0; b < player + 2; b++)
	{
		free(p[b]);
	}
	free(p);

	p = NULL;

	for (b = 0; b < player + 2; b++)
	{
		free(score[b]);
	}
	free(score);
}

void ten_frame(int a, int best, int **score, int **p)
{
	printf("10 frame \n");

	int i = 18;

	while (i == 18) // continue 사용하기 위해 반복문 
	{
		printf("1st score: "); // 1구 점수 받음
		scanf("%d", &score[a][i]);


		if (score[a][18] > 10) // 입력한 값이 10보다 크면
		{
			printf("\n오류 : 입력한 점수가 10보다 큽니다.\n\n"); // 경고 메세지 출력
			continue; // 입력으로 돌아감
		}

		printf("2nd score: "); // 2구 점수 받음
		scanf("%d", &score[a][i + 1]);

		if (score[a][19] > 10) // 입력한 값이 10보다 크면
		{
			printf("\n오류 : 입력한 점수가 10보다 큽니다.\n\n"); // 경고 메세지 출력
			continue; // 입력으로 돌아감
		}

		p[a][9] = score[a][18] + score[a][19];

		if (score[a][18] == 10 || p[a][9] == 10) // 스트라이크거나 스페어이면
		{
			i = 20;

			while (i == 20)
			{
				printf("3rd score: "); // 3구 점수 받는다
				scanf("%d", &score[a][i]);

				p[a][9] += score[a][20];

				if (score[a][20] > 10 || p[a][9] > 30) // 점수의 합이 30보다 크면
				{
					printf("\n오류 : 입력한 점수의 합이 30보다 큽니다.\n\n"); // 오류 메세지 출력
					continue; // 입력으로 돌아감
				}

				break;
			}
		}

		else if (p[a][9] > 10) // 입력 받은 점수의 합이 10보다 크면
		{
			printf("\n오류 : 입력한 점수의 합이 10보다 큽니다.\n\n"); // 오류 메세지 출력
			continue; // 입력으로 돌아간다
					  //i--;
		}

		else
			score[a][20] = 0;

		for (i = 18; i < BALL; i++)
		{
			if (score[a][i] == 10)
			{
				best++;
				strike_times(best);
			}
			else {
				best = 0;
			}
		}

		printf("\n");
		break;
	}
}

void calculation(int player, int a, int b, int **score, int **p, int *rank)
{
	int i;
	int **sum;

	sum = (int**)malloc((player + 2) * sizeof(int*));
	for (b = 0; b < (player + 2); b++)
	{
		sum[b] = (int *)malloc((FRAME + 2) * sizeof(int));
	}

	for (a = 0; a < player; a++)
	{
		for (b = 0; b < FRAME; b++)
		{
			sum[a][b] = 0;
		}
	}
	 
	for (a = 0; a < player; a++)
	{
		for (b = 0; b < FRAME; b++)
		{
			for (i = 0; i < BALL; i++)
			{
				if (score[a][i] == 10) // 스트라이크면
				{
					strike(a, b, i, sum, score, p); // strike 함수 호출
				}

				else if (score[a][i] != 10 && p[a][b] == 10) // 스페어면
				{
					spare(a, b, i, sum, score, p); // spare 함수 호출
				}

				else // 스페어와 스트라이크 모두 아니면
					stack(a, b, sum, p); // stack 함수 호출

				b++; // 프레임 Up
				i++; // 공 던진 횟수 up
			}
		}

		result_chart(a, sum, score); // 점수표를 출력하는 함수 호출
		rank[a] = sum[a][9];
	}
	total_rank(player, rank);

	for (b = 0; b < player + 2; b++)
	{
		free(sum[b]);
	}
	free(sum);
}

void strike(int a, int b, int i, int **sum, int **score, int **p)
{

	if (b == 0)
	{
		if (score[a][i + 2] == 10)
		{
			sum[a][0] = p[a][b] + p[a][b + 1] + score[a][i + 4];
		}
		else
			sum[a][0] = sum[a][0] + p[a][b] + p[a][b + 1];
	}

	else if (b > 0 && b < 8)
	{
		if (score[a][i + 2] == 10)
		{
			sum[a][b] = sum[a][b - 1] + p[a][b] + p[a][b + 1] + score[a][i + 4];
		}
		else
			sum[a][b] = sum[a][b - 1] + p[a][b] + p[a][b + 1];
	}

	else if (b == 8)
	{
		sum[a][8] = sum[a][7] + p[a][8] + score[a][18] + score[a][19];
	}

	else
		sum[a][9] = sum[a][8] + p[a][9];
}

void spare(int a, int b, int i, int **sum, int **score, int **p)
{
	if (b < 9)
	{
		if (b == 0)
		{
			sum[a][0] = p[a][b] + score[a][i + 2];
		}

		else
			sum[a][b] = sum[a][b - 1] + p[a][b] + score[a][i + 2];
	}

	else
		sum[a][9] = sum[a][8] + p[a][9];
}

void stack(int a, int b, int **sum, int **p)
{

	if (b == 0)
		sum[a][0] = p[a][b];

	else
		sum[a][b] = sum[a][b - 1] + p[a][b];
}

void result_chart(int a, int **sum, int **score)
{
	int i;

	printf("----------------------------------------------------------------------------------\n");
	printf("                             %d player 볼링 게임 결과                               \n", a + 1);
	printf("----------------------------------------------------------------------------------\n");
	printf("   1F  |   2F  |   3F  |   4F  |   5F  |   6F  |   7F  |   8F  |   9F  |    10F   \n");
	printf("----------------------------------------------------------------------------------\n");
	for (i = 0; i < 18; i++)
	{
		if (score[a][i] == 10)
		{
			printf("  X -  |");
		}

		else if (score[a][i] + score[a][i + 1] == 10)
		{
			printf("  %d /  |", score[a][i]);
		}

		else
			printf("  %d %d  |", score[a][i], score[a][i + 1]);

		i++;
	}
	for (i = 18; i < 21; i++) //수정한 부분
	{
		printf(" ");
		if (score[a][i] == 10)
		{
			printf(" X");
		}
		else if (i == 19 && score[a][i] + score[a][i - 1] == 10 && score[a][i - 1] != 10)
		{
			printf(" /");
		}
		else if (score[a][i] == 0)
		{
			printf(" -");
		}
		else {
			printf(" %d", score[a][i]);
		}
	}
	printf("\n");
	printf("----------------------------------------------------------------------------------\n");
	for (i = 0; i < FRAME; i++)
	{
		if (i < FRAME - 1)
			printf("   %d  |", sum[a][i]);
		else
			printf("   %d  \n", sum[a][i]);
	}
	printf("----------------------------------------------------------------------------------\n");
	printf("\n");
}

void strike_times(int best)
{
	switch (best)
	{
	case 1: printf("스트라이크!\n"); break;
	case 2: printf("더블!\n"); break;
	case 3: printf("터키!\n"); break;
	case 4: printf("포 베거!\n"); break;
	case 5: printf("파이브 베거!\n"); break;
	case 6: printf("식스 베거!\n"); break;
	case 7: printf("세븐 베거!\n"); break;
	case 8: printf("에잇 베거!\n"); break;
	case 9: printf("나인 베거!\n"); break;
	case 10: printf("텐 베거!\n"); break;
	case 11: printf("일레븐 베거!\n"); break;
	default: printf("퍼펙트 게임!\n"); break;
	}
}

void total_rank(int player, int *rank)
{
	int a, b;
	int number[4] = { 0 };


	for (a = 0; a < player; a++)
	{
		number[a] = a + 1;
	}

	for (a = 0; a < player; a++)
	{
		for (b = 0; b < player - 1; b++)
		{
			if (rank[a] < rank[a + 1])
			{
				bubble(&number[a], &number[a + 1]);
				bubble(&rank[a], &rank[a + 1]);
			}
		}
	}

	for (a = 0; a < player; a++)
	{
		printf("%d등은 %d번 선수로 %d점입니다.\n", a + 1, number[a], rank[a]);
	}

}

void bubble(int *i, int *j)
{
	int t = *i;
	*i = *j;
	*j = t;
}