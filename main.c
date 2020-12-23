#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//ALGORTIMA UZMANI BASTAN SIL CIFT YONLU KODU ALDIK!!!
struct komsu
{
    int plakaData;
    struct komsu *next;

};
struct sehir
{
    int komsuSayisi;
    char sehirAdi[100];
    char bolgeAdi[2];
    int plakaNo;
    struct sehir *onceki;
    struct sehir *sonraki;
    struct komsu *ko;

};
struct sehir* start=NULL;
struct sehir* temp=NULL;
struct sehir* son=NULL;
struct komsu* ilkk = NULL;
struct komsu* sonk=NULL;
struct komsu* geciciK=NULL;
void komsuSehirleriEkle()
{
    FILE *filep;
    filep=fopen("sehirler.txt","r");
    struct sehir* temp1=start;
    struct sehir* t1=start;
    struct sehir* temp2=NULL;
    int i=0,j;
    char komsusehiradi[25];
    char gecici[300];
    int  virgulSayisi=0;
    int komsuSayi=0;

    struct komsu* k=(struct komsu*) malloc(sizeof(struct komsu));

    struct komsu* k2=(struct komsu*) malloc(sizeof(struct komsu));

    while( t1!=NULL)
    {
        fgets(gecici,300,filep);
        virgulSayisi=0;
        komsuSayi=0;
        //printf("%s\n",gecici);
        for(j=0; gecici[j]!=NULL; j++)
        {
            if(gecici[j]==',')
            {
                virgulSayisi++;
                komsuSayi=virgulSayisi-2;
            }
        }
        //printf("%d--------------------------------\n",temp1->komsuSayisi);


        strtok(gecici,",");
        strtok(NULL,",");
        strtok(NULL,",");
        t1->komsuSayisi=komsuSayi;

        for(i=0; i<t1->komsuSayisi; i++)
        {

            strcpy(komsusehiradi,strtok(NULL,","));
            temp2=start;
            k=(struct komsu*) malloc(sizeof(struct komsu));
            while(temp2!=NULL)
            {
                if(strstr(komsusehiradi,temp2->sehirAdi))
                {
                    // printf(" ->%d",temp2->plakaNo);

                    k->plakaData=temp2->plakaNo;

                }

                temp2=temp2->sonraki;
            }

            k->next=NULL;

            if(t1->ko==NULL)
            {

                t1->ko=k;

            }

            else
            {

                if(t1->ko->plakaData > k->plakaData)
                {
                    k->next=t1->ko;
                    t1->ko=k;
                }

                else
                {
                    k2=t1->ko;

                    while(k2->next!=NULL)
                    {
                        if(k->plakaData < k2->next->plakaData)
                        {
                            k->next=k2->next;
                            k2->next=k;
                            break;
                        }
                        k2=k2->next;
                    }
                    k2->next=k;
                }


            }

        }

        printf("\n");
        t1=t1->sonraki;
    }
    //temp1=temp1->sonraki;

    // temp1->ko = k;

}

void yazdir()
{
    FILE *cikti = fopen("cikti.txt","w");
    temp=start;
    struct komsu *gezk;

    for(; temp != NULL ; temp = temp->sonraki)
    {
        if(temp->komsuSayisi==0)
        {
            printf("%d %s %s Komsu Sayisi: %d \n",temp->plakaNo,temp->sehirAdi,temp->bolgeAdi,temp->komsuSayisi);
            fprintf(cikti,"%d %s %s Komsu Sayisi: %d \n",temp->plakaNo,temp->sehirAdi,temp->bolgeAdi,temp->komsuSayisi);
            continue;
        }

        printf("%d %s %s Komsu Sayisi: %d ",temp->plakaNo,temp->sehirAdi,temp->bolgeAdi,temp->komsuSayisi);
        fprintf(cikti,"%d %s %s Komsu Sayisi: %d ",temp->plakaNo,temp->sehirAdi,temp->bolgeAdi,temp->komsuSayisi);
        for(gezk = temp->ko ; gezk != NULL ; gezk= gezk->next)
        {

            printf("-> %d  ",gezk->plakaData);
            fprintf(cikti,"-> %d ",gezk->plakaData);

        }
        printf("\n");
        fprintf(cikti,"\n");

    }
    fclose(cikti);


}
/*void basaEkle(struct sehir eklenecek)
{
    struct sehir* birinci= start;
    if(birinci==NULL)
    {
        birinci=eklenecek;
        return;
    }
    birinci->onceki=eklenecek;
    eklenecek->sonraki=birinci;
    birinci=eklenecek;
}
*/
void anaSehirEkle()
{
    FILE *dosya=fopen("sehirler.txt","r");
    //FILE *cikti=fopen("cikti.txt","w");
    char cumle[200];
    char kelime1[50];
    char kelime2[50];
    char *ayrac=", , '\n'";
    int komsuSayi=0;
    int virgulSayisi=0;
    int i,j;
    int sayi;

    while( fgets(cumle,200,dosya)!=NULL)
    {
        struct sehir* sehirler=(struct sehir*)malloc(sizeof(struct sehir));
        for(i=0; cumle[i]!=NULL; i++)
        {
            if(cumle[i]==',')
            {
                virgulSayisi++;
                komsuSayi=virgulSayisi-2;
            }

        }
        //printf("%d",komsuSayi);
        virgulSayisi=0;

        sayi=atoi(strtok(cumle,","));
        //printf(" %d ",sayi);
        strcpy(kelime1,strtok(NULL,","));
        //printf(" %s ",kelime1);
        strcpy(kelime2,strtok(NULL,","));
        //printf(" %s \n",kelime2);

        sehirler->plakaNo=sayi;
        strcpy(sehirler->sehirAdi,kelime1);
        strcpy(sehirler->bolgeAdi,kelime2);
        sehirler->komsuSayisi=komsuSayi;

        //sonaEkle(sehirler->plakaNo,sehirler->sehirAdi,sehirler->bolgeAdi,sehirler->komsuSayisi);
        //yazdir();

        if(start==NULL)
        {
            start=sehirler;
            son=sehirler;
            son->sonraki=NULL;
            son->ko=NULL;
        }
        /* start->onceki = sehirler;
         sehirler->sonraki = start;
         start=sehirler;*/
        else
        {
            son->sonraki=sehirler;
            sehirler->onceki=son;
            sehirler->sonraki=NULL;
            start->onceki=NULL;
            son=sehirler;
            sehirler->ko=NULL;
        }
    }
    fclose(dosya);
    //fclose(cikti);
}
void bolgeSehirListele(char bolgeAdi[2])
{
    FILE *cikti=fopen("cikti.txt","w");
    temp=start;
    while(temp!=NULL)
    {
        if(strstr(temp->bolgeAdi,bolgeAdi))
        {
            printf("%d,%s,%d\n",temp->plakaNo,temp->sehirAdi,temp->komsuSayisi);
            fprintf(cikti,"%d,%s,%d\n",temp->plakaNo,temp->sehirAdi,temp->komsuSayisi);
        }
        temp=temp->sonraki;
    }
    fclose(cikti);

}
void sehirIsimleAra(char sehirAdi[50])
{
    FILE *cikti=fopen("cikti.txt","w");
    struct sehir* q=start;
    struct komsu* gezKomsu;
    struct sehir* q2=start;
    char secim[15];
    char sehirAdii[50];
    char bolgeAdi[20];
    int plakaKodu;
    while(q!=NULL)
    {
        if(strstr(q->sehirAdi,sehirAdi))
        {
            break;
        }
        else
        {
            q=q->sonraki;
        }
        if(q==NULL)
        {
            printf("Sehir Listede Yok.\n Eklemek Ister misiniz?: ");
            scanf("%s",secim);

            if(strstr(secim,"evet"))
            {
                printf("Bolge:");
                scanf("%s",bolgeAdi);
                printf("Plaka kodu nedir:");
                scanf("%d",&plakaKodu);
                siraliEkle(sehirAdi,bolgeAdi,plakaKodu);
                yazdir();
            }
            if(strstr(secim,"hayir"))
            {

            }

        }
    }
    printf("%d %s %s Komsu sayisi: %d\n",q->plakaNo,q->sehirAdi,q->bolgeAdi,q->komsuSayisi);
    fprintf(cikti,"%d %s %s Komsu sayisi: %d\n",q->plakaNo,q->sehirAdi,q->bolgeAdi,q->komsuSayisi);
    for(; q2!=NULL; q2=q2->sonraki)
    {
        for(gezKomsu=q->ko; gezKomsu!=NULL; gezKomsu=gezKomsu->next)
        {
            if(q2->plakaNo==gezKomsu->plakaData)
            {
                printf("%s %s %d\n",q2->sehirAdi,q2->bolgeAdi,q2->plakaNo);
            }
        }
    }
    /*struct sehir* q3=start;
    while(q3!=NULL)
    {
        if(strstr(sehirAdi,q3->sehirAdi)==NULL)
        {
            printf("Sehir yok.Eklemek ister misiniz:\n");
            break;

        }
        q3=q3->sonraki;
    }
    printf("Eklemek ister misiniz:");
    scanf("%s",secim);
    {
        if(strstr(secim,"evet"))
        {

            printf("Bolge:");
            scanf("%s",bolgeAdi);
            printf("Plaka kodu nedir:");
            scanf("%d",&plakaKodu);
            siraliEkle(sehirAdi,bolgeAdi,plakaKodu);
            yazdir();
        }
        if(strstr(secim,"hayir"))
        {

        }
    }*/
    //printf("%s\n",q->sehirAdi);
    fclose(cikti);
}
void sehirPlakaylaAra(int plakaKodu)
{
    FILE *cikti=fopen("cikti.txt","w");
    struct sehir* q=start;
    struct komsu* gezKomsu;
    struct sehir* q2=start;
    char sehirAdi[100];
    char bolgeAdi[20];
    char secim[6];
    while(q!=NULL)
    {

        if(plakaKodu==q->plakaNo)
        {
            break;

        }
        else
        {
            q=q->sonraki;
        }
        if(q==NULL)
        {
            printf("Listede bu plakaya sahip sehir yoktur.\nEklemek ister misiniz?: ");
            scanf("%s",secim);
            if(strstr(secim,"evet"))
            {
                printf("Sehir Adi: ");
                scanf("%s",sehirAdi);
                printf("Bolge Adi: ");
                scanf("%s",bolgeAdi);
                siraliEkle(sehirAdi,bolgeAdi,plakaKodu);
                yazdir();
            }
            if(strstr(secim,"hayir"))
            {

            }
        }


    }
    printf("%d %s %s Komsu sayisi: %d\n",q->plakaNo,q->sehirAdi,q->bolgeAdi,q->komsuSayisi);
    fprintf(cikti,"%d %s %s Komsu sayisi: %d\n",q->plakaNo,q->sehirAdi,q->bolgeAdi,q->komsuSayisi);
    for(; q2!=NULL; q2=q2->sonraki)
    {
        for(gezKomsu=q->ko; gezKomsu!=NULL; gezKomsu=gezKomsu->next)
        {
            if(q2->plakaNo==gezKomsu->plakaData)
            {
                printf("%s %s %d\n",q2->sehirAdi,q2->bolgeAdi,q2->plakaNo);
            }
        }
    }
    /*struct sehir* q3=start;
    while(q3!=NULL)
    {
        if(plakaKodu!=q3->plakaNo)
        {
            printf("Sehir yok.Eklemek ister misiniz:\n");
            break;

        }
        q3=q3->sonraki;
    }
    printf("Eklemek ister misiniz:");
    scanf("%s",secim);
    {
        if(strstr(secim,"evet"))
        {
            printf("Isim:");
            scanf("%s",sehirAdi);
            printf("Bolge:");
            scanf("%s",bolgeAdi);
            siraliEkle(sehirAdi,bolgeAdi,plakaKodu);
            yazdir();
        }
        if(strstr(secim,"hayir"))
        {

        }
    }*/

    fclose(cikti);
}

void sehirSil(char sehirAdi[50])//ONUR GOK DERS NOTLARINDAN UYARLANDI.
{
    FILE *cikti=fopen("cikti.txt","w");
    //struct sehir* birinci = start;
    //struct sehir* ikinci = birinci->sonraki;
    struct sehir* silinecekSehir = start;
    while(silinecekSehir!=NULL)
    {
        if(strstr(silinecekSehir->sehirAdi,sehirAdi))
        {
            break;
        }
        else
        {
            silinecekSehir=silinecekSehir->sonraki;
        }
        if(silinecekSehir==NULL)
        {
            printf("Sehir listede yok.\n");
            fprintf(cikti,"Sehir listede yok.\n");
            break;

        }
    }

    if(silinecekSehir!=NULL)
    {
        if(silinecekSehir==start)
        {
            silinecekSehir->sonraki->onceki=NULL;
            start=start->sonraki;
            start->onceki=NULL;
        }
        else if(silinecekSehir==son)
        {
            silinecekSehir->onceki->sonraki=NULL;
            son=son->onceki;
            son->sonraki=NULL;
        }
        else
        {
            silinecekSehir->onceki->sonraki=silinecekSehir->sonraki;
            silinecekSehir->sonraki->onceki=silinecekSehir->onceki;
        }
        free(silinecekSehir);
        printf("Sehir silindi.\n");
        fprintf(cikti,"Sehir silindi.\n");
    }
    fclose(cikti);
}
struct komsu* silKomsu(int plaka)
{
    struct komsu* silinecekKomsu=ilkk;

    if(ilkk==NULL)
    {
        return NULL;
    }
    while(silinecekKomsu->plakaData!=plaka)
    {
        if(silinecekKomsu->next==NULL)
        {
            return NULL;
        }
        else
        {
            geciciK=silinecekKomsu;
            silinecekKomsu=silinecekKomsu->next;
        }
    }
    if(silinecekKomsu==ilkk)
    {
        ilkk=ilkk->next;
    }
    else
    {
        geciciK->next=silinecekKomsu->next;
    }
    return silinecekKomsu;


    /* while(silinecekKomsu!=NULL)
     {
         if(silinecekKomsu->plakaData==plaka)
         {
             break;
         }
         else
         {
             printf("Komsu Listede Yok.\n");
             silinecekKomsu=silinecekKomsu->next;
         }
     }
     if(silinecekKomsu!=NULL)
     {
         if(silinecekKomsu==ilkk)
         {
             if(ilkk->next==NULL)
             {
                 struct komsu* geciciKomsu = ilkk;
                 ilkk=ilkk->next;
                 free(geciciKomsu);
             }
             else
             {
                 free(ilkk);
                 ilkk=NULL;
             }
         }
         else if(silinecekKomsu==sonk)
         {
             if(ilkk==NULL)
             {
                 printf("Liste bos\n");
             }
             else
             {
                 struct komsu* geciciKomsu = ilkk;
                 if(ilkk->next==NULL)
                 {
                     free(ilkk);
                     ilkk=NULL;
                 }
                 else
                 {
                     while(geciciKomsu->next->next!=NULL)
                     {
                         geciciKomsu=geciciKomsu->next;
                     }
                     struct komsu* sonrakiKomsu = geciciKomsu->next;
                     free(sonrakiKomsu);
                     geciciKomsu->next=NULL;
                 }
             }
         }
         else
         {
             if(ilkk->plakaData==plaka)
             {
                 if(ilkk->next==NULL)
                 {
                     struct komsu* geciciKomsu = ilkk;
                     ilkk=ilkk->next;
                     free(geciciKomsu);
                 }
                 else
                 {
                     free(ilkk);
                     ilkk=NULL;
                 }
             }
             else
             {
                 struct komsu* geciciKomsu=ilkk;
                 while(geciciKomsu->next->plakaData!=plaka)
                 {
                     geciciKomsu=geciciKomsu->next;
                 }
                 struct komsu* geciciKomsu1 = geciciKomsu->next->next;
                 struct komsu* geciciKomsu2 = geciciKomsu;
                 free(geciciKomsu->next);
                 geciciKomsu2->next=geciciKomsu1;
             }
         }

     }*/

}
void siraliEkle(char sehirAdi[100], char bolgeAdi[20], int plaka )// algoritma uzmani basa ekle ve https:ckaynak.com/c-programlama-dili-tek-yonlu-bagli-liste-sirali-ekleme-ornegi-1318
{
    if(start==NULL)
    {
        struct sehir* ikinci=(struct sehir*)malloc(sizeof(struct sehir));
        strcpy(start->sehirAdi,sehirAdi);
        strcpy(start->bolgeAdi,bolgeAdi);
        start->plakaNo=plaka;
        start->sonraki=NULL;
    }

    else
    {

        if(start->plakaNo > plaka)
        {
            struct sehir* basaEklenecek=(struct sehir*)malloc(sizeof(struct sehir));
            strcpy(basaEklenecek->sehirAdi,sehirAdi);
            strcpy(basaEklenecek->bolgeAdi,bolgeAdi);
            basaEklenecek->plakaNo=plaka;
            if(start==NULL)
            {
                start=basaEklenecek;
            }
            start->onceki=basaEklenecek;
            basaEklenecek->sonraki=start;
            start=basaEklenecek;

        }
        else
        {
            temp=start;
            struct sehir* eklenecekSehir=(struct sehir*)malloc(sizeof(struct sehir*));
            strcpy(eklenecekSehir->sehirAdi,sehirAdi);
            strcpy(eklenecekSehir->bolgeAdi,bolgeAdi);
            eklenecekSehir->plakaNo=plaka;
            while(temp!=NULL)
            {
                if(temp->sonraki==NULL && (temp->plakaNo <= plaka))//sonaekleme
                {
                    eklenecekSehir->sonraki=NULL;
                    temp->sonraki=eklenecekSehir;
                    eklenecekSehir->ko=NULL;
                    break;
                }
                if((temp->sonraki->plakaNo) > plaka)//arayaekleme
                {
                    eklenecekSehir->sonraki=temp->sonraki;
                    temp->sonraki=eklenecekSehir;


                    break;
                }
                temp=temp->sonraki;
            }

        }
    }

}

void komsusuVarsaSil(char silinecekSehir[100])
{
    temp=start;
    struct sehir* temp2=start;
    struct komsu *gezk;
    int tutulanPlaka;

    for(; temp != NULL ; temp = temp->sonraki)
    {
        if(strstr(temp->sehirAdi,silinecekSehir))
        {
            tutulanPlaka=temp->plakaNo;
            //printf("%d\n",tutulanPlaka);
        }
        printf("\n");
    }

    for( ; temp2 != NULL ; temp2= temp2->sonraki)
    {
        for(gezk=temp2->ko; gezk != NULL ; gezk = gezk->next)
        {
            if(gezk->plakaData==tutulanPlaka)
            {
                //silKomsu(tutulanPlaka);
                temp2->komsuSayisi--;

                /*if(gezk->plakaData==ilkk->plakaData)
                {
                    geciciK=ilkk;
                    ilkk=ilkk->next;
                    free(geciciK);
                }
                else
                {
                    while(ilkk->next!=NULL)
                    {
                        if(ilkk->next->plakaData==tutulanPlaka)
                        {
                            geciciK=ilkk->next;
                            if(geciciK==sonk)
                            {

                            }
                        }
                    }
                }*/

            }

        }
        // printf("\n");
    }


}
void komsuEkle (int plaka)//https:ckaynak.com/c-programlama-dili-tek-yonlu-bagli-liste-sirali-ekleme-ornegi-1318
{
    if(ilkk==NULL)
    {
        // struct komsu* ikinci=(struct komsu*)malloc(sizeof(struct komsu));
        start->ko->plakaData=plaka;
        start->ko->next=NULL;
    }

    else
    {

        if(start->ko->plakaData > plaka)
        {
            struct komsu* basaEklenecek=(struct komsu*)malloc(sizeof(struct komsu));
            basaEklenecek->plakaData=plaka;
            if(ilkk==NULL)
            {
                ilkk=basaEklenecek;
            }
            basaEklenecek->next=ilkk;
            ilkk=basaEklenecek;

        }
        else
        {
            geciciK=ilkk;
            struct komsu* eklenecekSehir=(struct komsu*)malloc(sizeof(struct komsu*));
            eklenecekSehir->plakaData=plaka;
            while(geciciK!=NULL)
            {
                if(geciciK->next==NULL && (geciciK->plakaData <= plaka))//sonaekleme
                {
                    eklenecekSehir->next=NULL;
                    geciciK->next=eklenecekSehir;
                    break;
                }
                if((geciciK->next->plakaData) > plaka)//arayaekleme
                {
                    eklenecekSehir->next=geciciK->next;
                    geciciK->next=eklenecekSehir;
                    break;
                }
                geciciK=geciciK->next;
            }
        }
    }
}
int main()
{
    int secim;
    char bolge[2];
    char sehirad[50];
    int sayi,arananPlaka;
    int arananSecim;
    char kosul[10];
    int kosulSayi;
    char sehirAdi[100];
    char bolgeAdi[5];
    int sehirPlaka;
    char silinecekSehirAd[50];
    char secim2[10];//yeni sehir ekleyelim mi
    char secim3[10];//yeni sehre komsu eklemek ister misiniz
    char komsuAdlari[100][100];
    int i;
    int komsuSayisi;
    int komsuPlaka;
    char yazi[100];
    char komsuEklenecekSehir[50], eklenecekKomsu[50];
    anaSehirEkle();
    komsuSehirleriEkle();
    yazdir();

    while(1)
    {
        printf("MENU\n\n");
        printf("1-Sehir Ekle: \n");
        printf("2-Komsu Ekle: \n");
        printf("3-Sehir Ara: \n");
        printf("4-Sehir Sil: \n");
        printf("5-Sehir Bilgileri Listele(Ayni bolgedeki): \n");
        printf("6-Ortak Ozellige Gore Listele(Kosul): \n");
        printf("7-Girilen Aralikta Komsu Sayisi Olanlarin Ortak Komsularini Listele:\n");
        printf("8-Cikis: \n\n");
        printf("Seciminiz: ");
        scanf("%d",&secim);
        printf("\n");

        if(secim==1)
        {
            //fprintf(cik)
            temp=start;
            struct sehir* q=start;

            printf("Eklemek istediginiz sehir ismi nedir:");
            scanf("%s",sehirAdi);
            printf("Eklemek istediginiz bolge adi nedir:");
            scanf("%s",bolgeAdi);
            printf("Eklemek istediginiz sehrin plakasi nedir:");
            scanf("%d",&sehirPlaka);
            /*   while(q!=NULL)
               {
                   if(strstr(q->sehirAdi,sehirAdi) && strstr(q->bolgeAdi,bolgeAdi) && q->plakaNo==sehirPlaka)
                   {
                       break;
                   }
                   else
                   {
                       q=q->sonraki;
                   }
                   if(q==NULL)
                   {
                       printf("Sehir Listede Yok.\n Eklemek Ister misiniz?: ");
                       scanf("%s",secim);

                       if(strstr(secim,"evet"))
                       {

                           siraliEkle(sehirAdi,bolgeAdi,sehirPlaka);
                           yazdir();
                       }
                       if(strstr(secim,"hayir"))
                       {

                       }

                   }
               }
               printf("Sehir listede var.\n");
            */
            while(temp!=NULL)
            {
                if(strstr(sehirAdi,temp->sehirAdi) && strstr(bolgeAdi,temp->bolgeAdi)  && sehirPlaka==temp->plakaNo)
                {
                    printf("Listede ayni kayitta sehir vardir.\n");

                }
                if(strstr(sehirAdi,temp->sehirAdi)== NULL && strstr(bolgeAdi,temp->bolgeAdi)==NULL  && sehirPlaka!=temp->plakaNo)
                {

                    strcpy(yazi,"yok");
                }
                temp=temp->sonraki;
            }

            if(strstr(yazi,"yok"))
            {
                printf("Sehir yok.\n");
                printf("Eklemek ister misiniz:(evet-hayir)");
                scanf("%s",secim2);
                if(strstr(secim2,"evet"))
                {
                    siraliEkle(sehirAdi,bolgeAdi,sehirPlaka);
                    yazdir();

                }
                if(strstr(secim2,"hayir"))
                {
                    printf("Eklemek istemediniz\n");
                }
            }
        }



        if(secim==2)
        {
            char komsusehiradi[50];
            int eklenecekKomsuPlaka;
            int geciciPlaka;
            printf("Hangi Sehre Komsu Eklemek Istersiniz?: ");
            scanf("%s",komsuEklenecekSehir);
            printf("Eklemek istediginiz komsu adi?: ");
            scanf("%s",eklenecekKomsu);
            printf("Plakasini giriniz: ");
            scanf("%d",&eklenecekKomsuPlaka);

            struct sehir* tempS = start;
            struct komsu* tempK = (struct komsu*) malloc(sizeof(struct komsu));
            struct sehir* tempS2 = start;
            struct sehir* temp2;

            for(; tempS!=NULL ; tempS=tempS->sonraki)
            {
                if (strstr(tempS->sehirAdi,komsuEklenecekSehir))
                {
                    tempS->komsuSayisi++;
                    printf("\n");
                    geciciPlaka=tempS->plakaNo;

                    for(i=0; i<tempS->komsuSayisi; i++)
                    {
                        //eklenecekKomsuPlaka=tempS->ko->plakaData;
                        temp2=start;
                        struct komsu* k=(struct komsu*) malloc(sizeof(struct komsu));
                        k->plakaData=eklenecekKomsuPlaka;
                        k->next=NULL;

                        if(tempS->ko==NULL)
                        {
                            tempS->ko=k;
                            break;
                        }
                        else
                        {
                            if(tempS->ko->plakaData > k->plakaData)
                            {
                                k->next=tempS->ko;
                                tempS->ko=k;
                                break;
                            }
                            else
                            {
                                tempK=tempS->ko;

                                while(tempK->next!=NULL)
                                {
                                    if(k->plakaData < tempK->next->plakaData)
                                    {
                                        k->next=tempK->next;
                                        tempK->next=k;
                                        break;
                                    }
                                    tempK=tempK->next;
                                }
                                tempK->next=k;
                                break;
                            }
                        }
                    }
                }
            }

            for(; tempS2!=NULL ; tempS2=tempS2->sonraki)
            {
                if (strstr(tempS2->sehirAdi,eklenecekKomsu))
                {
                    tempS2->komsuSayisi++;
                    printf("\n");

                    for(i=0; i<tempS2->komsuSayisi; i++)
                    {
                        //eklenecekKomsuPlaka=tempS->ko->plakaData;
                        temp2=start;
                        struct komsu* k=(struct komsu*) malloc(sizeof(struct komsu));
                        k->plakaData=geciciPlaka;
                        k->next=NULL;

                        if(tempS2->ko==NULL)
                        {
                            tempS2->ko=k;
                            break;
                        }
                        else
                        {
                            if(tempS2->ko->plakaData > k->plakaData)
                            {
                                k->next=tempS2->ko;
                                tempS2->ko=k;
                                break;
                            }
                            else
                            {
                                tempK=tempS2->ko;

                                while(tempK->next!=NULL)
                                {
                                    if(k->plakaData < tempK->next->plakaData)
                                    {
                                        k->next=tempK->next;
                                        tempK->next=k;
                                        break;
                                    }
                                    tempK=tempK->next;
                                }
                                tempK->next=k;
                                break;
                            }
                        }
                    }
                }
            }

            yazdir();

        }

        if(secim==3)
        {

            printf("Isimle aratmak icin 1'e, Plaka ile aratmak icin 2'e basiniz:");
            scanf("%d",&arananSecim);
            if(arananSecim==1)
            {
                printf("Sehir ismini giriniz: ");
                scanf("%s",sehirad);
                sehirIsimleAra(sehirad);
            }
            if(arananSecim==2)
            {
                printf("Plaka giriniz: ");
                scanf("%d",&arananPlaka);
                sehirPlakaylaAra(arananPlaka);
            }

        }
        if(secim==4)
        {
            struct sehir* temp4 = start;
            printf("Silmek istediginiz sehir ismini giriniz: ");
            scanf("%s",silinecekSehirAd);
            komsusuVarsaSil(silinecekSehirAd);
            sehirSil(silinecekSehirAd);

            yazdir();


        }
        if(secim==5)
        {

            printf("Hangi Bolgedeki Sehirleri Listelemek Istiyorsunuz?(AK,GA,EG,DA,IA,MA,KA): ");
            scanf("%s",bolge);
            bolgeSehirListele(bolge);
        }
        if(secim==6)
        {
            int aralik2;
            printf("Hangi sayiyla karsilastirmak istersiniz?: ");
            scanf("%d",&kosulSayi);
            printf("Karsilastirma kelimeniz?(sayidan-buyuk,kucuk,esit): ");
            scanf("%s",kosul);
            temp=start;
            while(temp!=NULL)
            {
                if(strstr(kosul,"buyuk") && kosulSayi<temp->komsuSayisi)
                {
                    printf("%d %s %s %d\n",temp->plakaNo,temp->sehirAdi,temp->bolgeAdi,temp->komsuSayisi);
                }
                if(strstr(kosul,"kucuk") && kosulSayi>temp->komsuSayisi)
                {
                    printf("%d %s %s %d\n",temp->plakaNo,temp->sehirAdi,temp->bolgeAdi,temp->komsuSayisi);
                }
                if(strstr(kosul,"esit") && kosulSayi==temp->komsuSayisi)
                {
                    printf("%d %s %s %d\n",temp->plakaNo,temp->sehirAdi,temp->bolgeAdi,temp->komsuSayisi);
                }
                temp=temp->sonraki;
            }


        }
        if(secim==7)
        {
            int aralik1,aralik2;
            struct sehir* temp71=start;
            struct sehir* temp72;
            struct komsu* tempK=ilkk;
            struct sehir* temp73=start;
            struct komsu* tempK2=ilkk;
            printf("Baslangic sinirinizi giriniz: ");
            scanf("%d",&aralik1);
            printf("Bitis sinirinizi giriniz: ");
            scanf("%d",&aralik2);

            int tutulanPlaka1;
            int tutulanPlaka2;
            for(; temp71!=NULL ; temp71=temp71->sonraki)
            {
                if(aralik1<temp71->komsuSayisi && temp71->komsuSayisi<aralik2)
                {

                    printf("%d %s %d\n",temp71->plakaNo,temp71->sehirAdi,temp71->komsuSayisi);

                    for(tempK=temp71->ko ; tempK!=NULL ; tempK=tempK->next)
                    {
                        temp72=temp71->sonraki;
                        for(;  temp72!=NULL; temp72=temp72->sonraki)
                        {
                            if(aralik1<temp71->komsuSayisi&& temp71->komsuSayisi<aralik2)
                            {
                                for(tempK2=temp72->ko ; tempK2!=NULL ; tempK2 = tempK2->next)
                                {
                                    if(tempK->plakaData == tempK2->plakaData)
                                    {
                                        printf("%s ve %s sehri %d' e komsu \n",temp71->sehirAdi,temp72->sehirAdi,tempK2->plakaData);
                                    }
                                }
                            }

                        }

                    }


                }
            }

        }
        if(secim==8)
        {
            break;
        }
    }
    return 0;
}
