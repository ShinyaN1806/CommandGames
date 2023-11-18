#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int dispgameno(void){
  printf("遊びたいゲームの番号を入力してください。\n");
  printf("-------------------------------------\n");
  printf("1：じゃんけん\n");
  printf("-------------------------------------\n");
  printf("0を入力すると終了します。\n");
  return 0;
}

int janken(void){
  const int WAIT_SECOND = 2; // 待機秒数
  const int LOSE_MAX = 3; //3回負けるとアウト
  const char VIEWRULE_KEY = '0';
  enum {GU = 1, CHOKI = 2, PA = 3};
  const char GU_KEY = '1', CHOKI_KEY = '2', PA_KEY = '3';
  
  printf("ルールを見る場合は%d、見ない場合はそれ以外のキーを入力してください。\n", VIEWRULE_KEY - '0');
  char viewrule;
  scanf("%s", &viewrule);
  if (viewrule == VIEWRULE_KEY){
    printf("★ルール説明★\n");
    printf("グー・チョキ・パーのいずれかを出し、勝ち負けを競います。\n");
    printf("グーはチョキに勝ち、パーに負けます。\n");
    printf("チョキはパーに勝ち、グーに負けます。\n");
    printf("パーはグーに勝ち、チョキに負けます。\n");
    printf("同じ手を出したら、あいことなり、もう一度やり直しになります。\n");
    printf("グーは1、チョキは2、パーは3を入力してください。 \n");
    printf("これ以外のものを入力すると負けになります。 \n");
    printf("3回負けるとそこでゲームオーバーとなります。\n");
    printf("★ルール説明おわり★\n");
  }
  int score = 0;
  int retry = LOSE_MAX;
  char player;
  int playerhand;
  int opponenthand;
  bool draw = false;
  srand((unsigned)time(0UL));
  while(1){
    if (draw) {
      printf("あいこ、で、しょ！（%d：グー・%d：チョキ・%d：パー）\n", GU, CHOKI, PA);
    } else {
      printf("残り%d回負けるとゲームオーバーです。\n", retry);
      printf("最初はグー！じゃん、けん、ぽん！（%d：グー・%d：チョキ・%d：パー）\n", GU, CHOKI, PA);
    }
    draw = false;
    scanf("%s", &player);
    if (player == GU_KEY || player == CHOKI_KEY || player == PA_KEY) {
      playerhand = player - '0';
      opponenthand = rand() % 3 + 1;
      switch (playerhand){
        case GU:
          printf("あなた：グー\n");
          break;
        case CHOKI:
          printf("あなた：チョキ\n");
          break;
        case PA:
          printf("あなた：パー\n");
          break;
      }
      switch (opponenthand){
        case GU:
          printf("相手：グー\n");
          break;
        case CHOKI:
          printf("相手：チョキ\n");
          break;
        case PA:
          printf("相手：パー\n");
          break;
      }
      if (playerhand == opponenthand) {
        draw = true;
      }
      else if  (playerhand == GU && opponenthand == CHOKI ||
                playerhand == CHOKI && opponenthand == PA ||
                playerhand == PA && opponenthand == GU) {
        printf("あなたの勝ちです！\n");
        score++;
      }
      else {
        printf("残念、あなたの負けです。\n");
        retry--;
      }
    } else {
      printf("変な値が入力されました。負けです。\n");
        retry--;
    }
    if (retry == 0) {
      printf("ゲームオーバーです。\n");
      break;
    }
    sleep(WAIT_SECOND);
  }
  printf("あなたのスコアは%d点です。\n", score);
  sleep(WAIT_SECOND);
  return 0;
}

int main(void){
  printf("ゲームスタート！\n");
  while(1){
    dispgameno();
    char gameno;
    scanf("%s", &gameno);
    if (gameno == '0'){
      break;
    }
    switch (gameno){
      case '1':
        printf("じゃんけんを開始します。\n");
        janken();
        break;
      default:
        printf("選択肢にないものが入力されました。\n");
    }
  }
  return 0;
}