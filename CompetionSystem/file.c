#include "file.h"

Status loadCompetitorFromFile(SeqList *list,char* filename){
	Competitor e;
	FILE *fp = fopen(filename,"r");
	if(fp == NULL)
		return ERROR;

	while(fscanf(fp,"%s",e.name) != -1){
		e.point = 0;
		ListPushBack(list,e);
	}
	fclose(fp);
	return OK;
}

Status saveIndividualResult(SeqList list){
	FILE *fp = fopen(INDIVIDUAL_RESULT_FILE,"w");
	Competitor e;
	int i;
	if(fp == NULL)
		return ERROR;

	for(i=0;i<ListLength(list);++i){
		GetElem(list,i,&e);
		fprintf(fp,"%s\t%3d分\t%s\n",e.name,e.point,e.point>60?"入围":"淘汰");
	}
	fclose(fp);
	return OK;
}

Status saveTeamResult(SeqList list){
	FILE *fp = fopen(TEAM_RESULT_FILE,"w");
	Competitor e;
	int i;
	if(fp == NULL)
		return ERROR;

	for(i=0;i<ListLength(list);++i){
		GetElem(list,i,&e);
		fprintf(fp,"%s\t%3d分\n",e.name,e.point);
	}
	fclose(fp);
	return OK;
}
