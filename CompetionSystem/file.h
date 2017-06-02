#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include "seqlist.h"

#define TEAM_DATA_FILE "team.txt"		//小组赛数据文件
#define INDIVIDUAL_DATA_FILE "individual.txt"//个人赛数据文件
#define TEAM_RESULT_FILE "team_result.txt"		//小组赛结果文件
#define INDIVIDUAL_RESULT_FILE "individual_result.txt"		//个人赛结果文件

Status loadCompetitorFromFile(SeqList *list,char* filename);
//从名为filename的文件中读取参赛队伍或参赛者的名称，文件不存在返回ERROR
Status saveIndividualResult(SeqList list);
//保存个人比赛结果
Status saveTeamResult(SeqList list);
//保存小组赛结果

#endif
