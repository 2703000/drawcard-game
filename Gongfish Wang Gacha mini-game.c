/*    Gongfish Wang Gacha mini-game
    Copyright (C) 2024  Chenghao Zhang,Xuyao Li,Zhengyuan Xu

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#define GOLD_CARD_COUNT 5
#define TOTAL_CARD_COUNT 100
#define RESET_COUNT 80

typedef enum
{
	COMMON_CARD,
	GOLD_CARD,
	GOLD_WATER_CARD,
	GOLD_FIRE_CARD,
	GOLD_EARTH_CARD,
	GOLD_WOOD_CARD,
	GOLD_KINGFISH_CARD
} CardType;

int coins = 50;					// ��ʼӲ������
int drawCount = 0;				// �鿨����
CardType cards[100];			// �洢�鵽�Ŀ�

const char *coinsFilename = "coins.dat";	// ����Ӳ���ļ���
const char *drawCountFilename = "drawCount.dat";	// ����鿨�����ļ���
const char *cardsFilename = "cards.dat";	// ����鿨����ļ���

void saveCoins()
{
	FILE *file = fopen(coinsFilename, "w");
	if (file == NULL)
	{
		printf("�޷�����Ӳ���ļ���\n");
		return;
	}
	fprintf(file, "%d\n", coins);
	fclose(file);
	printf("Ӳ�������ѱ��档\n");
	Sleep(500);
}

void saveDrawCount()
{
	FILE *file = fopen(drawCountFilename, "w");
	if (file == NULL)
	{
		printf("�޷������鿨�����ļ���\n");
		return;
	}
	fprintf(file, "%d\n", drawCount);
	fclose(file);
	printf("�鿨�����ѱ��档\n");
	Sleep(500);
}

void saveCards()
{
	FILE *file = fopen(cardsFilename, "a");
	if (file == NULL)
	{
		printf("�޷������鿨����ļ���\n");
		Sleep(500);
		return;
	}
	for (int i = 0; i < drawCount; i++)
	{
		switch (cards[i])
		{
		case GOLD_CARD:
			fprintf(file, "GOLD_CARD\n");
			break;
		case GOLD_WATER_CARD:
			fprintf(file, "GOLD_WATER_CARD\n");
			break;
		case GOLD_FIRE_CARD:
			fprintf(file, "GOLD_FIRE_CARD\n");
			break;
		case GOLD_EARTH_CARD:
			fprintf(file, "GOLD_EARTH_CARD\n");
			break;
		case GOLD_WOOD_CARD:
			fprintf(file, "GOLD_WOOD_CARD\n");
			break;
		case GOLD_KINGFISH_CARD:
			fprintf(file, "GOLD_KINGFISH_CARD\n");
			break;
		default:
			fprintf(file, "COMMON_CARD\n");
			break;
		}
	}
	fclose(file);
	printf("�鿨����ѱ��档\n");
	Sleep(500);
}

void loadCoins()
{
	FILE *file = fopen(coinsFilename, "r");
	if (file == NULL)
	{
		printf("δ�ҵ�Ӳ���ļ�����ʼ����Ϸ��\n");
		Sleep(500);
		return;
	}
	fscanf(file, "%d", &coins);
	fclose(file);
	printf("Ӳ���������ڼ���...\n");
	printf("Ӳ�������Ѽ��ء�\n");
	Sleep(500);
}

void loadDrawCount()
{
	FILE *file = fopen(drawCountFilename, "r");
	if (file == NULL)
	{
		printf("δ�ҵ��鿨�����ļ�����ʼ����Ϸ��\n");
		return;
	}
	fscanf(file, "%d", &drawCount);
	fclose(file);
	printf("�鿨�������ڼ���...\n");
	printf("�鿨�����Ѽ��ء�\n");
	Sleep(500);
}

void loadCards()
{
	FILE *file = fopen(cardsFilename, "r");
	if (file == NULL)
	{
		printf("δ�ҵ��鿨����ļ�����ʼ����Ϸ��\n");
		Sleep(500);
		return;
	}
	char cardTypeStr[20];		// �洢��ȡ���ַ���
	for (int i = 0; i < drawCount; i++)
	{
		fscanf(file, "%s", cardTypeStr);
		if (strcmp(cardTypeStr, "GOLD_CARD") == 0)
			cards[i] = GOLD_CARD;
		else if (strcmp(cardTypeStr, "GOLD_WATER_CARD") == 0)
			cards[i] = GOLD_WATER_CARD;
		else if (strcmp(cardTypeStr, "GOLD_FIRE_CARD") == 0)
			cards[i] = GOLD_FIRE_CARD;
		else if (strcmp(cardTypeStr, "GOLD_EARTH_CARD") == 0)
			cards[i] = GOLD_EARTH_CARD;
		else if (strcmp(cardTypeStr, "GOLD_WOOD_CARD") == 0)
			cards[i] = GOLD_WOOD_CARD;
		else if (strcmp(cardTypeStr, "GOLD_KINGFISH_CARD") == 0)
			cards[i] = GOLD_KINGFISH_CARD;
		else
			cards[i] = COMMON_CARD;
	}
	fclose(file);
	printf("�鿨������ڼ���...\n");
	printf("�鿨����Ѽ��ء�\n");
	Sleep(500);
}

CardType drawCard()
{
	if (drawCount >= RESET_COUNT)
	{
		drawCount = 0;			// �鿨�������㣬���������cards����
	}

	if (drawCount < RESET_COUNT)
	{
		if (drawCount % 10 == 0)	// ʮ����ʱ
		{
			return GOLD_CARD;
		}
		else if (drawCount < 80)	// ����ʱ
		{
			int randomValue = rand() % 100;
			if (randomValue < GOLD_CARD_COUNT)
			{
				int specialValue = rand() % 100;
				if (specialValue < 25)	// 25%���ʻ�ý𿨱���
				{
					int variant = rand() % 6;
					switch (variant)
					{
					case 0:
						return GOLD_WATER_CARD;
					case 1:
						return GOLD_FIRE_CARD;
					case 2:
						return GOLD_EARTH_CARD;
					case 3:
						return GOLD_WOOD_CARD;
					case 4:
						return GOLD_KINGFISH_CARD;
					default:
						return GOLD_CARD;
					}
				}
				else
				{
					return GOLD_CARD;
				}
			}
			else
			{
				return COMMON_CARD;
			}
		}
		else					// 80���Ժ�س���
		{
			return GOLD_CARD;
		}
	}

	return GOLD_CARD;			// �鿨��������󣬵���س���
}

void singleDraw()
{
	if (coins < 1)
	{
		printf("Ӳ�Ҳ��㣬�޷����е��顣\n");
		Sleep(500);
		return;
	}
	coins--;
	CardType card = drawCard();
	cards[drawCount++] = card;	// ��¼�鵽�Ŀ�
	if (card == GOLD_CARD)
	{
		printf("�𿨣�");
	}

	else if (card == GOLD_WATER_CARD)
	{
		printf("ˮϵ���������������㣡");
	}

	else if (card == GOLD_FIRE_CARD)
	{
		printf("��ϵ���������������㣡");
	}

	else if (card == GOLD_EARTH_CARD)
	{
		printf("��ϵ���������������㣡");
	}

	else if (card == GOLD_WOOD_CARD)
	{
		printf("ľϵ���������������㣡");
	}

	else if (card == GOLD_KINGFISH_CARD)
	{
		printf("�����㣡��������һ����ƶ�����������ѧ��ҵ��");
	}

	else
	{
		printf("��ͨ����");
	}
	printf("ʣ��Ӳ�ң�%d\n", coins);
	Sleep(500);
}

void tenDraws()
{
	if (coins < 10)
	{
		printf("Ӳ�Ҳ��㣬�޷�����ʮ���顣\n");
		return;
	}
	coins -= 10;
	printf("ʮ��������\n\n");
	int goldCount = 0;
	for (int i = 0; i < 10; i++)
	{
		CardType card = drawCard();
		cards[drawCount++] = card;	// ��¼�鵽�Ŀ�
		if (card == GOLD_CARD)
		{
			printf("�𿨣�\n");
			goldCount++;
		}

		else if (card == GOLD_WATER_CARD)
		{
			printf("ˮϵ���������������㣡\n");
			goldCount++;
		}

		else if (card == GOLD_FIRE_CARD)
		{
			printf("��ϵ���������������㣡\n");
			goldCount++;
		}

		else if (card == GOLD_EARTH_CARD)
		{
			printf("��ϵ���������������㣡\n");
			goldCount++;
		}

		else if (card == GOLD_WOOD_CARD)
		{
			printf("ľϵ���������������㣡\n");
			goldCount++;
		}

		else if (card == GOLD_KINGFISH_CARD)
		{
			printf("�����㣡��������һ����ƶ�����������ѧ��ҵ��\n");
			goldCount++;
		}

		else
		{
			printf("��ͨ����\n");
		}
		Sleep(60);
	}
	printf("\nʮ�����������鵽�� %d �Ž𿨡�\n", goldCount);
	printf("ʣ��Ӳ�ң�%d\n", coins);
	Sleep(500);
}

void displayCards()
{
	printf("\n��ĳ鿨������£�\n");
	for (int i = 0; i < drawCount; i++)
	{
		switch (cards[i])
		{
		case GOLD_CARD:
			printf("�� %d �ſ�����\n", i + 1);
			break;
		case GOLD_WATER_CARD:
			printf("�� %d �ſ���ˮϵ����������������\n", i + 1);
			break;
		case GOLD_FIRE_CARD:
			printf("�� %d �ſ�����ϵ����������������\n", i + 1);
			break;
		case GOLD_EARTH_CARD:
			printf("�� %d �ſ�����ϵ����������������\n", i + 1);
			break;
		case GOLD_WOOD_CARD:
			printf("�� %d �ſ���ľϵ����������������\n", i + 1);
			break;
		case GOLD_KINGFISH_CARD:
			printf("�� %d �ſ��������㣬����һ����ƶ�\n", i + 1);
			break;
		case COMMON_CARD:
			printf("�� %d �ſ�����ͨ��\n", i + 1);
			break;
		}
	}
}

int main()
{
	char choise[100];
	char choice[100];
	char continueGame[100];
	printf("��ӭ����������鿨С��Ϸ��\n");

	printf("\n�����������ʲô��\n");
	printf("1. �鿨\n");
	printf("2. �鿴\n");
	printf("3. ����\n");
	printf("4. ����\n");
	printf("���������ѡ�񣨳鿨 �� �鿴 �� ���� �� ��������");
	scanf("%s", choise);
	if (strcmp(choise, "�鿨") == 0)
	{
		Sleep(1);
		loadCoins();			// ����Ӳ������
		loadDrawCount();		// ���س鿨����
		loadCards();			// ���س鿨���

		srand(time(NULL));		// ��ʼ�������������

		Sleep(1);
		
		do
		{
			system("cls");
			printf("��ѡ��鿨��ʽ��\n");
			printf("1. ����\n");
			printf("2. ʮ����\n");
			printf("���������ѡ��1 �� 2����");
			scanf("%s", choice);

			if (strcmp(choice, "1") == 0)
			{
				printf("\n����һ�γ鿨��\n");
				singleDraw();
			}
			else if (strcmp(choice, "2") == 0)
			{
				printf("\n����ʮ���飺\n");
				tenDraws();
			}
			else
			{
				printf("����������������룡\n");
			}

			printf("\n�Ƿ������Ϸ������/�񣩣�");
			scanf("%s", continueGame);

		}
		while (strcmp(continueGame, "��") == 0 || strcmp(continueGame, "yes") == 0
			   || strcmp(continueGame, "Yes") == 0);

		saveCoins();			// ����Ӳ������
		saveDrawCount();		// ����鿨����
		saveCards();			// ����鿨���

		printf("\n��Ϸ��������л���Ĳ��룡\n");
		Sleep(2);
		system("cls");
		main();
	}

	else if (strcmp(choise, "�鿴") == 0)
	{
		char comeback[100];
		loadDrawCount();		// ���س鿨����
		loadCards();			// ���س鿨���
		Sleep(1);
		do
		{

			displayCards();		// ��ʾ�鿨���
			printf("\n���롰q�����أ�");
			scanf("%s", comeback);
			if (strcmp(comeback, "q") == 0)
			{
				Sleep(1);
				printf("���Եȣ�������ת\n");
				Sleep(1);
				system("cls");
				main();
			}
		}
		while (strcmp(comeback, "q") != 0);

	}

	else if (strcmp(choise, "����") == 0)
	{
		system("cls");
		loadCoins();			// ����Ӳ������
		coins += 100;
		printf("�Ѽ�һ��\n����һ�¶��ѣ���ʽ��ɾ��^O^\n");
		saveCoins();			// ����Ӳ������
		Sleep(500);
		system("cls");
		main();
	}
	else if (strcmp(choise, "����") == 0)
	{
		printf("�������˳�\n");
		Sleep(1);
		return 0;
	}
}
