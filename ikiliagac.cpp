#include <iostream>
#include <stdlib.h>

using namespace std;

struct agac
{
	int veri;
	struct agac *pSol;
	struct agac *pSag;
};

typedef struct agac A;


void ekle(A **agac,int veri){

	if(*agac == NULL){
		A *yeni = (A*)malloc(sizeof(A));
		yeni->pSag = NULL;
		yeni->pSol = NULL;
		yeni->veri = veri;
		*agac = yeni;
		return;
	}else{
	A *tmp = *agac;
	if(tmp->veri > veri){
		if(tmp->pSol != NULL){
			return ekle(&(tmp->pSol),veri);
		}
		A *yeni = (A*)malloc(sizeof(A));
		yeni->pSag = NULL;
		yeni->pSol = NULL;
		yeni->veri = veri;
		tmp->pSol = yeni;

	}else if(tmp->veri < veri){
		if(tmp->pSag != NULL){
			return ekle(&(tmp->pSag),veri);
		}
		A *yeni = (A*)malloc(sizeof(A));
		yeni->pSag = NULL;
		yeni->pSol = NULL;
		yeni->veri = veri;
		tmp->pSag = yeni;
	}
}
}

void goster(A *agac){
	if(agac != NULL){
	goster(agac->pSol);
	cout<<agac->veri<<endl;
	goster(agac->pSag);
	}

}


A* ara(A **agac,int veri){
	A *tmp = *agac;
	if(tmp != NULL){
		if(tmp->veri > veri){
			if(tmp->pSol != NULL){
				return ara(&(tmp->pSol),veri);
			}
			return NULL;
		}else if(tmp->veri < veri){
			if(tmp->pSag != NULL){
				return ara(&(tmp->pSag),veri);
			}
			return NULL;
		}else{
			return tmp;
		}
	}
	return NULL;	
}

A* enkucuk(A** agac){
	A *tmp = *agac;

		if(tmp->pSol !=NULL){
			return enkucuk(&(tmp->pSol));
		}
		return tmp;
}

void sil(A **agac,int veri,A** ebeveyn){

	A *tmp = *agac;
	if(tmp->veri > veri){
		if(tmp->pSol != NULL){
			return sil(&(tmp->pSol),veri,&tmp);
		}
		return;
	}else if(tmp->veri < veri){
		if(tmp->pSag != NULL){
			return sil(&(tmp->pSag),veri,&tmp);
		}
		return;
	}


	if(tmp->pSol == NULL && tmp->pSag == NULL){
		if((*ebeveyn)->pSag == tmp){
			(*ebeveyn)->pSag = NULL;
		}else{
			(*ebeveyn)->pSol = NULL;
		}
	}else if(tmp->pSol != NULL && tmp->pSag != NULL){
			A* enkuck = enkucuk(&(tmp->pSag));
			A *tmp2 = tmp;
			if((*ebeveyn)->pSol == tmp){
				(*ebeveyn)->pSol = enkuck;
			}else{
				(*ebeveyn)->pSag = enkuck;
			}

			sil(&(tmp2->pSag),enkuck->veri,&tmp2);
	}else if(tmp->pSol != NULL){
		if((*ebeveyn)->pSol == tmp){
			(*ebeveyn)->pSol = tmp->pSol;
		}else{
			(*ebeveyn)->pSag = tmp->pSol;
		}
	}else{
		if((*ebeveyn)->pSol == tmp){
			(*ebeveyn)->pSol = tmp->pSag;
		}else{
			(*ebeveyn)->pSag = tmp->pSag;
		}
	}	
}


int main(){

	A *kok = NULL;
	ekle(&kok,32);
	ekle(&kok,10);
	ekle(&kok,40);
	ekle(&kok,66);

	goster(kok);

 /*
	A *aranan = ara(&kok,40);
	if(aranan != NULL){
		cout<<"Aranan deger:"<<aranan->veri<<endl;
	}else{
		cout<<"Aranan deger bulunanamadi"<<endl;
	}
*/

	sil(&kok,40,NULL);
	cout<<"---------------------"<<endl;
	goster(kok);	
}