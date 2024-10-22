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

int coins = 50;					// 初始硬币数量
int drawCount = 0;				// 抽卡次数
CardType cards[100];			// 存储抽到的卡

const char *coinsFilename = "coins.dat";	// 定义硬币文件名
const char *drawCountFilename = "drawCount.dat";	// 定义抽卡次数文件名
const char *cardsFilename = "cards.dat";	// 定义抽卡结果文件名

void saveCoins()
{
	FILE *file = fopen(coinsFilename, "w");
	if (file == NULL)
	{
		printf("无法创建硬币文件。\n");
		return;
	}
	fprintf(file, "%d\n", coins);
	fclose(file);
	printf("硬币数量已保存。\n");
	Sleep(500);
}

void saveDrawCount()
{
	FILE *file = fopen(drawCountFilename, "w");
	if (file == NULL)
	{
		printf("无法创建抽卡次数文件。\n");
		return;
	}
	fprintf(file, "%d\n", drawCount);
	fclose(file);
	printf("抽卡次数已保存。\n");
	Sleep(500);
}

void saveCards()
{
	FILE *file = fopen(cardsFilename, "a");
	if (file == NULL)
	{
		printf("无法创建抽卡结果文件。\n");
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
	printf("抽卡结果已保存。\n");
	Sleep(500);
}

void loadCoins()
{
	FILE *file = fopen(coinsFilename, "r");
	if (file == NULL)
	{
		printf("未找到硬币文件，开始新游戏。\n");
		Sleep(500);
		return;
	}
	fscanf(file, "%d", &coins);
	fclose(file);
	printf("硬币数量正在加载...\n");
	printf("硬币数量已加载。\n");
	Sleep(500);
}

void loadDrawCount()
{
	FILE *file = fopen(drawCountFilename, "r");
	if (file == NULL)
	{
		printf("未找到抽卡次数文件，开始新游戏。\n");
		return;
	}
	fscanf(file, "%d", &drawCount);
	fclose(file);
	printf("抽卡次数正在加载...\n");
	printf("抽卡次数已加载。\n");
	Sleep(500);
}

void loadCards()
{
	FILE *file = fopen(cardsFilename, "r");
	if (file == NULL)
	{
		printf("未找到抽卡结果文件，开始新游戏。\n");
		Sleep(500);
		return;
	}
	char cardTypeStr[20];		// 存储读取的字符串
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
	printf("抽卡结果正在加载...\n");
	printf("抽卡结果已加载。\n");
	Sleep(500);
}

CardType drawCard()
{
	if (drawCount >= RESET_COUNT)
	{
		drawCount = 0;			// 抽卡次数归零，但不会清空cards数组
	}

	if (drawCount < RESET_COUNT)
	{
		if (drawCount % 10 == 0)	// 十连抽时
		{
			return GOLD_CARD;
		}
		else if (drawCount < 80)	// 单抽时
		{
			int randomValue = rand() % 100;
			if (randomValue < GOLD_CARD_COUNT)
			{
				int specialValue = rand() % 100;
				if (specialValue < 25)	// 25%几率获得金卡变种
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
		else					// 80次以后必出金
		{
			return GOLD_CARD;
		}
	}

	return GOLD_CARD;			// 抽卡次数归零后，单抽必出金
}

void singleDraw()
{
	if (coins < 1)
	{
		printf("硬币不足，无法进行单抽。\n");
		Sleep(500);
		return;
	}
	coins--;
	CardType card = drawCard();
	cards[drawCount++] = card;	// 记录抽到的卡
	if (card == GOLD_CARD)
	{
		printf("金卡！");
	}

	else if (card == GOLD_WATER_CARD)
	{
		printf("水系！可以升级王贡鱼！");
	}

	else if (card == GOLD_FIRE_CARD)
	{
		printf("火系！可以升级王贡鱼！");
	}

	else if (card == GOLD_EARTH_CARD)
	{
		printf("土系！可以升级王贡鱼！");
	}

	else if (card == GOLD_WOOD_CARD)
	{
		printf("木系！可以升级王贡鱼！");
	}

	else if (card == GOLD_KINGFISH_CARD)
	{
		printf("王贡鱼！他赐予你一个大逼斗并叫你做数学作业！");
	}

	else
	{
		printf("普通卡。");
	}
	printf("剩余硬币：%d\n", coins);
	Sleep(500);
}

void tenDraws()
{
	if (coins < 10)
	{
		printf("硬币不足，无法进行十连抽。\n");
		return;
	}
	coins -= 10;
	printf("十连抽结果：\n\n");
	int goldCount = 0;
	for (int i = 0; i < 10; i++)
	{
		CardType card = drawCard();
		cards[drawCount++] = card;	// 记录抽到的卡
		if (card == GOLD_CARD)
		{
			printf("金卡！\n");
			goldCount++;
		}

		else if (card == GOLD_WATER_CARD)
		{
			printf("水系！可以升级王贡鱼！\n");
			goldCount++;
		}

		else if (card == GOLD_FIRE_CARD)
		{
			printf("火系！可以升级王贡鱼！\n");
			goldCount++;
		}

		else if (card == GOLD_EARTH_CARD)
		{
			printf("土系！可以升级王贡鱼！\n");
			goldCount++;
		}

		else if (card == GOLD_WOOD_CARD)
		{
			printf("木系！可以升级王贡鱼！\n");
			goldCount++;
		}

		else if (card == GOLD_KINGFISH_CARD)
		{
			printf("王贡鱼！他赐予你一个大逼斗并叫你做数学作业！\n");
			goldCount++;
		}

		else
		{
			printf("普通卡。\n");
		}
		Sleep(60);
	}
	printf("\n十连抽结束，你抽到了 %d 张金卡。\n", goldCount);
	printf("剩余硬币：%d\n", coins);
	Sleep(500);
}

void displayCards()
{
	printf("\n你的抽卡结果如下：\n");
	for (int i = 0; i < drawCount; i++)
	{
		switch (cards[i])
		{
		case GOLD_CARD:
			printf("第 %d 张卡：金卡\n", i + 1);
			break;
		case GOLD_WATER_CARD:
			printf("第 %d 张卡：水系，可以升级王贡鱼\n", i + 1);
			break;
		case GOLD_FIRE_CARD:
			printf("第 %d 张卡：火系，可以升级王贡鱼\n", i + 1);
			break;
		case GOLD_EARTH_CARD:
			printf("第 %d 张卡：土系，可以升级王贡鱼\n", i + 1);
			break;
		case GOLD_WOOD_CARD:
			printf("第 %d 张卡：木系，可以升级王贡鱼\n", i + 1);
			break;
		case GOLD_KINGFISH_CARD:
			printf("第 %d 张卡：王贡鱼，给你一个大逼斗\n", i + 1);
			break;
		case COMMON_CARD:
			printf("第 %d 张卡：普通卡\n", i + 1);
			break;
		}
	}
}

int main()
{
	char choise[100];
	char choice[100];
	char continueGame[100];
	printf("欢迎来到王贡鱼抽卡小游戏！\n");

	printf("\n请输入你想干什么：\n");
	printf("1. 抽卡\n");
	printf("2. 查看\n");
	printf("3. 任务\n");
	printf("4. 结束\n");
	printf("请输入你的选择（抽卡 或 查看 或 任务 或 结束）：");
	scanf("%s", choise);
	if (strcmp(choise, "抽卡") == 0)
	{
		Sleep(1);
		loadCoins();			// 加载硬币数量
		loadDrawCount();		// 加载抽卡次数
		loadCards();			// 加载抽卡结果

		srand(time(NULL));		// 初始化随机数生成器

		Sleep(1);
		
		do
		{
			system("cls");
			printf("请选择抽卡方式：\n");
			printf("1. 单抽\n");
			printf("2. 十连抽\n");
			printf("请输入你的选择（1 或 2）：");
			scanf("%s", choice);

			if (strcmp(choice, "1") == 0)
			{
				printf("\n进行一次抽卡：\n");
				singleDraw();
			}
			else if (strcmp(choice, "2") == 0)
			{
				printf("\n进行十连抽：\n");
				tenDraws();
			}
			else
			{
				printf("输入错误，请重新输入！\n");
			}

			printf("\n是否继续游戏？（是/否）：");
			scanf("%s", continueGame);

		}
		while (strcmp(continueGame, "是") == 0 || strcmp(continueGame, "yes") == 0
			   || strcmp(continueGame, "Yes") == 0);

		saveCoins();			// 保存硬币数量
		saveDrawCount();		// 保存抽卡次数
		saveCards();			// 保存抽卡结果

		printf("\n游戏结束，感谢您的参与！\n");
		Sleep(2);
		system("cls");
		main();
	}

	else if (strcmp(choise, "查看") == 0)
	{
		char comeback[100];
		loadDrawCount();		// 加载抽卡次数
		loadCards();			// 加载抽卡结果
		Sleep(1);
		do
		{

			displayCards();		// 显示抽卡结果
			printf("\n输入“q”返回：");
			scanf("%s", comeback);
			if (strcmp(comeback, "q") == 0)
			{
				Sleep(1);
				printf("请稍等，正在跳转\n");
				Sleep(1);
				system("cls");
				main();
			}
		}
		while (strcmp(comeback, "q") != 0);

	}

	else if (strcmp(choise, "任务") == 0)
	{
		system("cls");
		loadCoins();			// 加载硬币数量
		coins += 100;
		printf("已加一百\n测试一下而已，正式版删除^O^\n");
		saveCoins();			// 保存硬币数量
		Sleep(500);
		system("cls");
		main();
	}
	else if (strcmp(choise, "结束") == 0)
	{
		printf("程序已退出\n");
		Sleep(1);
		return 0;
	}
}
