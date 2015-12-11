#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
#include <string.h>

void menuFonk(int);
void s2_UyeGirisi();
void s3_UyeKayit();
void s4_YoneticiGirisi();
void yoneticiMenuFonk(int);
void kitapEkle();
void uyeGirisiSonrasi(int);
void s1_misafirGirisi();
void kitapSil();

FILE *uyeler;
FILE *uyelerOku;
FILE *yonetici;
FILE *kitaplar;
FILE *kitaplarSilme;
FILE *satinal;
FILE *kitaplarAdet;

char globaluyeName[100] = "uyeKullaniciAdi";

int main(){
	
	theFrontPage:
		
	setlocale(LC_ALL, "Turkish"); // T�rk�e karakterleri destekler.
	
	int secim;
	
	menuFonk(0);
	
	while(1){
		
		printf("\n\n Se�im yap�n: "); scanf("%d", &secim);
		
		if ( secim == 1 || secim == 2 || secim == 3 || secim == 4 ){
			
			system("cls"); // Ekran� temizler.
		
			break;
		
		}else{
			
			system("cls");
			
			menuFonk(1);
			
		}
	
	}
	
	if ( secim == 1 ){
		
		printf("\n Misafir Giri�i yapt�n�z.");
		
		printf("\n\n Misafir olarak sadece t�m kitaplar�n listesini g�rebilirsiniz.");
		
		s1_misafirGirisi();
		
		printf("\n Bir �nceki men�ye d�nmek i�in herhangi bir tu�a bas�n�z.");
	
		if ( getche() != 'e' ){
			
			system("cls");
			
			goto theFrontPage;
		
		}
		
	}else if ( secim == 2 ){
		
		printf("\n �ye Giri�i yapabilmek i�in bilgilerinizi girin.");
		
		s2_UyeGirisi();
		
	}else if ( secim == 3 ){
		
		printf("\n Kay�t olabilmek i�in bilgilerinizi girin.");
		
		s3_UyeKayit();
		
	}else if ( secim == 4 ){
	
		printf("\n Y�netici Giri�i yapabilmek i�in bilgilerinizi girin.");
		
		s4_YoneticiGirisi();
		
	}
	
	printf("\n\n"); system("pause");
	return 0;
	
}

void menuFonk(int hata){

	printf("\n\t\t\t\t- - - MEN� - - -\n\n");
	printf(" [1] - Misafir Giri�i  ");
	printf("[2] - �ye Giri�i  ");
	printf("[3] - �ye Kay�t  ");
	printf("[4] - Y�netici Giri�i");
	
	if ( hata == 1 ){ printf("\n\n Men�de olmayan, hatal� bir se�im yapt�n�z. L�tfen yeniden se�im yap�n."); }

}

void s2_UyeGirisi(){
	
	char uyeKAdi[25], uyeSifre[25], ArauyeKAdi[250][25], ArauyeSifre[250][25];
	int KAdivarmi, Sifrevarmi, kullaniciVar = 0, i = 0;
	
	while(1){
	
		printf("\n\n Kullan�c� Ad�: "); scanf("%s", &uyeKAdi);
		printf("\n �ifre: "); scanf("%s", &uyeSifre);
		
		uyeler = fopen("uyeler.txt", "r"); // r ifadesi sadece okuma yapar.
		
		while( !feof(uyeler) ){ // Dosyan�n sonuna gelinceye kadar s�rekli bu i�lemleri yap.
			
			fscanf(uyeler, "%s %s", &ArauyeKAdi[i], &ArauyeSifre[i]);
			
			KAdivarmi = strcmp(ArauyeKAdi[i], uyeKAdi);
			Sifrevarmi = strcmp(ArauyeSifre[i], uyeSifre);
			
			if ( KAdivarmi == 0 && Sifrevarmi == 0 ){
				
				kullaniciVar = 1; break;
				
			}
			
			i = i + 1;
			
		}
		
		if ( kullaniciVar == 1 ){
		
			printf("\n Ba�ar�yla sisteme giri� yapt�n�z!");
			
			system("cls");
			
			strcpy(globaluyeName, uyeKAdi);
			
			uyeGirisiSonrasi(0);
			
			break;
		
		}else{
			
			system("cls");
			
			printf("\n Girdi�iniz bilgiler sistemde kay�tl� de�il. L�tfen yeniden giri� yap�n.");
			
		}
		
		fclose(uyeler);
		
	}
	
}

void s3_UyeKayit(){
	
	char uyeKAdi[25], uyeSifre[25], ArauyeKAdi[250][25], ArauyeSifre[250][25];
	int KAdivarmi, kullaniciVar = 0, i = 0;
	
	while( 1 ){
	
		printf("\n\n Kullan�c� Ad�: "); scanf("%s", &uyeKAdi);
		printf("\n �ifre: "); scanf("%s", &uyeSifre);
		
		uyeler = fopen("uyeler.txt", "a"); // a ifadesi sonuna ekleme yapar.
		
		uyelerOku = fopen("uyeler.txt", "r");
		
		kullaniciVar = 0;
		
		while( !feof(uyelerOku) ){
				
			fscanf(uyelerOku, "%s %s", &ArauyeKAdi[i], &ArauyeSifre[i]);
			
			KAdivarmi = strcmp(ArauyeKAdi[i], uyeKAdi);
			
			if ( KAdivarmi == 0 ){
				
				kullaniciVar = 1; break;
				
			}
			
			i = i + 1;
			
		}
		
		if ( kullaniciVar == 1 ){
			
			system("cls");
			
			printf("\n Girdi�iniz kullan�c� ad� sisteme daha �nce kay�t edilmi�.");
			
			printf("\n\n L�tfen yeniden kay�t olmay� deneyin.");
			
		}else{
			
			break;
			
		}
		
	}
	
	fprintf(uyeler, "\n%s %s", uyeKAdi, uyeSifre);
			
	printf("\n Ba�ar�yla sisteme kay�t oldunuz!");
	
	system("cls");
	
	strcpy(globaluyeName, uyeKAdi);
	
	fclose(uyeler);
	
	fclose(uyelerOku);
	
	uyeGirisiSonrasi(0);
	
}

void s4_YoneticiGirisi(){
	
	char yoneticiKAdi[25], yoneticiSifre[25], AraYoneticiKAdi[25][25], AraYoneticiSifre[25][25];
	int KAdivarmi, Sifrevarmi, yoneticiVar = 0, i = 0;
	
	int yoneticiSecim;
	
	while(1){
	
		printf("\n\n Kullan�c� Ad�: "); scanf("%s", &yoneticiKAdi);
		printf("\n �ifre: "); scanf("%s", &yoneticiSifre);
		
		yonetici = fopen("yonetici.txt", "r");
		
		while( !feof(yonetici) ){
			
			fscanf(yonetici, "%s %s", &AraYoneticiKAdi[i], &AraYoneticiSifre[i]);
			
			KAdivarmi = strcmp(AraYoneticiKAdi[i], yoneticiKAdi);
			Sifrevarmi = strcmp(AraYoneticiSifre[i], yoneticiSifre);
			
			if ( KAdivarmi == 0 && Sifrevarmi == 0 ){
				
				yoneticiVar = 1; break;
				
			}
			
			i = i + 1;
			
		}
		
		if ( yoneticiVar == 1 ){
		
			printf("\n Ba�ar�yla y�netici olarak sisteme giri� yapt�n�z!");
			
			system("cls");
			
			yoneticiMenuFonk(0);
			
			while(1){
		
				printf("\n\n Se�im yap�n: "); scanf("%d", &yoneticiSecim);
				
				if ( yoneticiSecim == 1 || yoneticiSecim == 2 || yoneticiSecim == 3 ){
					
					system("cls");
				
					break;
				
				}else{
					
					system("cls");
					
					yoneticiMenuFonk(1);
					
				}
			
			}
			
			if ( yoneticiSecim == 1 ){
				
				printf("\n Kitap ekleyebilmek i�in kitap bilgilerini girin.");
				
				kitapEkle();
				
			}else if ( yoneticiSecim == 2 ){
				
				kitapSil();
				
			}else if ( yoneticiSecim == 3 ){
				
				printf("\n Kitap sat�n alan t�m �yeleri ve bilgilerini a�a��dan g�rebilirsiniz.");
				
				char kitapAlanUye[250][100], kitapSatilanAdi[250][100];
				int tarihG[250], tarihA[250], tarihY[250], saat1[250], saat2[250], saat3[250], adedi[250], fiyati[250], i = 0;
				
				satinal = fopen("satinal.txt", "r");
				
				printf("\n\n\n �ye Kullan�c� Ad� - Kitap Ad� - Al�nan Adet - Fiyat - Ald��� Tarih ve Saat\n\n");
					
				while( !feof(satinal) ){
					
					fscanf(satinal, "%s - %s - %d - %d - %d.%d.%d - %d:%d:%d", &kitapAlanUye[i], &kitapSatilanAdi[i], &adedi[i], &fiyati[i], &tarihG[i], &tarihA[i], &tarihY[i], &saat1[i], &saat2[i], &saat3[i]);
				
					printf(" %d-) %s - %s - %d Adet - %d TL - %d.%d.%d - %d:%d:%d\n\n", i+1, kitapAlanUye[i], kitapSatilanAdi[i], adedi[i], fiyati[i], tarihG[i], tarihA[i], tarihY[i], saat1[i], saat2[i], saat3[i]);
					
					i = i + 1;
					
				}
				
				fclose(satinal);
				
			}
			
			printf("\n Admin paneline d�nmek i�in herhangi bir tu�a bas�n�z.");
			
			if ( getche() != 'e' ){
			
				system("cls");
				
				printf("\n Yeniden i�lem yapmak i�in Admin Giri�i yap�n.");
				
				s4_YoneticiGirisi();
				
			}
			
			break; // Y�netici var ise bitiyor.
		
		}else{
			
			system("cls");
			
			printf("\n Girdi�iniz y�netici bilgileri do�ru de�il. L�tfen yeniden giri� yap�n.");
			
		}
		
		fclose(yonetici);
		
	}
	
}

void yoneticiMenuFonk(int hata){

	printf("\n\t\t\t- - - Y�NET�C� MEN�S� - - -\n\n");
	printf(" [1] - Kitap Ekle  ");
	printf("[2] - Kitap Sil  ");
	printf("[3] - Sat�n Alma Listesi");
	
	if ( hata == 1 ){ printf("\n\n Men�de olmayan, hatal� bir se�im yapt�n�z. L�tfen yeniden se�im yap�n."); }

}

void kitapEkle(){
	
	char kitapAdi[100], kitapYazari[100];
	int kitapFiyati, kitapStok;
	
	printf("\n\n Kitap Ad�: "); scanf("%s", &kitapAdi);
	printf("\n Kitap Yazar�: "); scanf("%s", &kitapYazari);
	printf("\n Kitap Adet Fiyat�: "); scanf("%d", &kitapFiyati);
	printf("\n Kitap Stok Adedi: "); scanf("%d", &kitapStok);
	
	kitaplar = fopen("kitaplar.txt", "a");
	
	fprintf(kitaplar, "\n%s - %s - %d - %d", kitapAdi, kitapYazari, kitapFiyati, kitapStok);
	
	printf("\n Kitap ba�ar�yla sisteme kay�t edildi!");
	
	printf("\n\n Admin paneline d�nmek i�in herhangi bir tu�a bas�n�z.");
	
	fclose(kitaplar);
	
	if ( getche() != 'e' ){
			
		system("cls");
		
		printf("\n Yeniden i�lem yapmak i�in Admin Giri�i yap�n.");
		
		s4_YoneticiGirisi();
		
	}
	
}

void uyeGirisiSonrasi(int hata){
	
	int secim;
	
	errorUsersMenu:
		
	usersMainMenu:
	
	printf("\n\t\t\t  - - -  �YE MEN�S� - - -\n\n");
	printf(" [1] - T�m Kitaplar� Listele  ");
	printf("[2] - Kitap Sat�n Al  ");
	printf("[3] - Kitap Ara  ");
	
	if ( hata == 1 ){ printf("\n\n Men�de olmayan, hatal� bir se�im yapt�n�z. L�tfen yeniden se�im yap�n."); }
	
	while(1){
		
		printf("\n\n Se�im yap�n: "); scanf("%d", &secim);
		
		if ( secim == 1 || secim == 2 || secim == 3 ){
			
			system("cls"); // Ekran� temizler.
		
			break;
		
		}else{
			
			system("cls");
			
			hata = 1;
			
			goto errorUsersMenu;
			
		}
	
	}
	
	if ( secim == 1 ){
		
		printf("\n T�m kitaplar�n listesini a�a��dan g�rebilirsiniz.");
		
		s1_misafirGirisi();
		
		printf("\n Bir �nceki men�ye d�nmek i�in herhangi bir tu�a bas�n�z.");
	
		if ( getche() != 'e' ){
			
			system("cls");
			
			hata = 0; goto usersMainMenu;
		
		}
		
	}else if ( secim == 2 ){
		
		char kitapAdi[250][100], kitapYazari[250][100], kitapAdiGelen[100], hangiKitapAl[100], hangiKitapYazari[100];
		int kitapFiyati[250], kitapStok[250], i = 0, kitapVarmiymis = 0, kitapVarmi, evetHayir, hangiKitapFiyati, hangiKitapStok, kacAdetAlcan, sonFiyat;
		
		kitaplar = fopen("kitaplar.txt", "r"); // Okunacak dosya yeri
		
		printf("\n Sat�n Almak �stedi�iniz Kitap Ad�: "); scanf("%s", &kitapAdiGelen);
		
		while( !feof(kitaplar) ){
			
			fscanf(kitaplar, "%s - %s - %d - %d", &kitapAdi[i], &kitapYazari[i], &kitapFiyati[i], &kitapStok[i]);
			
			kitapVarmi = strcmp(kitapAdi[i], kitapAdiGelen);
			
			if ( kitapVarmi == 0 ){
				
				printf("\n\n Kitap Ad� - Kitap Yazar� - Kitap Fiyat� - Kitap Stok Adedi \n\n");
				
				printf(" %s - %s - %d TL - %d Adet Stokta Mevcut", kitapAdi[i], kitapYazari[i], kitapFiyati[i], kitapStok[i]);
				
				kitapVarmiymis = 1;
				
				strcpy(hangiKitapAl, kitapAdi[i]);
				
				strcpy(hangiKitapYazari, kitapYazari[i]);
				
				hangiKitapFiyati = kitapFiyati[i];
				
				hangiKitapStok = kitapStok[i];
				
				while( 1 ){
					
					printf("\n\n Sat�n Almak �stedi�iniz Kitap Adedi: "); scanf("%d", &kacAdetAlcan);
					
					if ( kacAdetAlcan > hangiKitapStok ){
						
						printf("\n\n Mevcut stok say�s�ndan daha fazla kitap adedi girdiniz!");
						
					}else{
						
						hangiKitapStok = kitapStok[i] - kacAdetAlcan;
						
						break;
						
					}
					
				}
				
				sonFiyat = kacAdetAlcan * hangiKitapFiyati;
				
				printf("\n\n �denecek Fatura Tutar�: %d TL", sonFiyat);
				
				break;
			
			}else{
				
				kitapVarmiymis = 2;
				
			}
			
		}
		
		if ( kitapVarmiymis == 2 ){
			
			printf("\n Arad���n�z kitap ad� ile uyu�an herhangi bir kitap bulunamad�!");
			
			printf("\n\n Bir �nceki men�ye d�nmek i�in herhangi bir tu�a bas�n�z.");
		
			fclose(kitaplar);
		
			if ( getche() != 'e' ){
				
				system("cls");
				
				hata = 0; goto usersMainMenu;
			
			}
			
		}else if ( kitapVarmiymis = 1 ){
			
			printf("\n\n ��lemi onaylamak i�in '1', iptal etmek i�in '0' tu�una bas�n�z. "); scanf("%d", &evetHayir);
			
			if ( evetHayir == 1 ){
				
				/* Tarih i�in.. */
				
				time_t rawtime;
			    struct tm * timeinfo;
			
			    time (&rawtime);
			    timeinfo = localtime(&rawtime);
			    
			    /* Tarih i�in.. */
			    
			    satinal = fopen("satinal.txt", "a");
			    
			    fprintf(satinal, "\n%s - %s - %d - %d - %d.%d.%d - %d:%d:%d", globaluyeName, hangiKitapAl, kacAdetAlcan, sonFiyat, timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
			
				printf("\n\n Kitab� ba�ar�yla sat�n ald�n�z.");
				
				/* Kitap Stok Adedini D���rme */
				
				kitaplarAdet = fopen("kitaplarAdet.txt", "w"); // Yaz�lacak dosya yeri
				
				fclose(kitaplar);
				
				kitaplar = fopen("kitaplar.txt", "r");
				
				i = 0;
				
				while( !feof(kitaplar) ){
			
					fscanf(kitaplar, "%s - %s - %d - %d", &kitapAdi[i], &kitapYazari[i], &kitapFiyati[i], &kitapStok[i]);
					
					kitapVarmi = strcmp(kitapAdi[i], hangiKitapAl);
					
					if ( kitapVarmi != 0 ){
					
						fprintf(kitaplarAdet, "\n%s - %s - %d - %d", kitapAdi[i], kitapYazari[i], kitapFiyati[i], kitapStok[i]);
						
					}
					
					i = i + 1;
					
				}
				
				fclose(kitaplarAdet);
				
				fclose(kitaplar);
				
				fclose(satinal);
				
				/* Her �eyi kapatt�m. En son kitap stok adedini d���rece�im. */
				
				kitaplarAdet = fopen("kitaplarAdet.txt", "a");
				
				fprintf(kitaplar, "\n%s - %s - %d - %d", hangiKitapAl, hangiKitapYazari, hangiKitapFiyati, hangiKitapStok);
				
				fclose(kitaplarAdet);
				
				remove("kitaplar.txt");
				rename("kitaplarAdet.txt","kitaplar.txt");
				
				printf("\n\n Bir �nceki men�ye d�nmek i�in herhangi bir tu�a bas�n�z.");
		
				if ( getche() != 'e' ){
					
					system("cls");
					
					hata = 0; goto usersMainMenu;
				
				}
				
			}else{
				
				printf("\n\n Sat�n alma i�lemini iptal ettiniz.");
				
				printf("\n\n Bir �nceki men�ye d�nmek i�in herhangi bir tu�a bas�n�z.");
				
				fclose(kitaplar);
		
				if ( getche() != 'e' ){
					
					system("cls");
					
					hata = 0; goto usersMainMenu;
				
				}
				
			}
			
		}
		
	}else if ( secim == 3 ){
		
		char kitapAdi[250][100], kitapYazari[250][100], kitapAdiGelen[100];
		int kitapFiyati[250], kitapStok[250], i = 0, kitapVarmiymis = 0, kitapVarmi;
		
		kitaplar = fopen("kitaplar.txt", "r"); // Okunacak dosya yeri
		
		printf("\n Aranacak Kitap Ad�: "); scanf("%s", &kitapAdiGelen);
		
		while( !feof(kitaplar) ){
		
			fscanf(kitaplar, "%s - %s - %d - %d", &kitapAdi[i], &kitapYazari[i], &kitapFiyati[i], &kitapStok[i]);
			
			kitapVarmi = strcmp(kitapAdi[i], kitapAdiGelen);
			
			if ( kitapVarmi == 0 ){
				
				printf("\n\n Kitap Ad� - Kitap Yazar� - Kitap Fiyat� - Kitap Stok Adedi \n\n");
				
				printf(" %s - %s - %d TL - %d Adet Stokta Mevcut", kitapAdi[i], kitapYazari[i], kitapFiyati[i], kitapStok[i]);
				
				kitapVarmiymis = 1;
				
				break;
			
			}else{
				
				kitapVarmiymis = 2;
				
			}
			
		}
		
		if ( kitapVarmiymis == 2 ){
			
			printf("\n Arad���n�z kitap ad� ile uyu�an herhangi bir kitap bulunamad�!");
			
		}
		
		printf("\n\n Bir �nceki men�ye d�nmek i�in herhangi bir tu�a bas�n�z.");
		
		fclose(kitaplar);
	
		if ( getche() != 'e' ){
			
			system("cls");
			
			hata = 0; goto usersMainMenu;
		
		}
		
	}

}

void s1_misafirGirisi(){
	
	char kitapAdi[250][100], kitapYazari[250][100];
	int kitapFiyati[250], kitapStok[250], i = 0;
	
	kitaplar = fopen("kitaplar.txt", "r");
	
	printf("\n\n\n Kitap Ad� - Kitap Yazar� - Kitap Fiyat� - Kitap Stok Adedi \n\n");
		
	while( !feof(kitaplar) ){
		
		fscanf(kitaplar, "%s - %s - %d - %d", &kitapAdi[i], &kitapYazari[i], &kitapFiyati[i], &kitapStok[i]);
		
		if ( (kitapFiyati[i] != 0) && (kitapStok[i] != 0) ){
	
			printf(" %d-) %s - %s - %d TL - %d Adet\n\n", i+1, kitapAdi[i], kitapYazari[i], kitapFiyati[i], kitapStok[i]);
		
		}
		
		i = i + 1;
		
	}
	
	fclose(kitaplar);
	
}

void kitapSil(){
	
	char kitapAdi[250][100], kitapYazari[250][100], kitapAdiGelen[100];
	int kitapFiyati[250], kitapStok[250], i = 0, kitapVarmiymis = 0, kitapVarmi;
	
	kitaplar = fopen("kitaplar.txt", "r"); // Okunacak dosya yeri
	kitaplarSilme = fopen("kitaplarSilme.txt", "w"); // Yaz�lacak dosya yeri
	
	printf("\n Silinecek Kitap Ad�: "); scanf("%s", &kitapAdiGelen);
	
	while( !feof(kitaplar) ){
		
		fscanf(kitaplar, "%s - %s - %d - %d", &kitapAdi[i], &kitapYazari[i], &kitapFiyati[i], &kitapStok[i]);
		
		kitapVarmi = strcmp(kitapAdi[i], kitapAdiGelen);
		
		if ( kitapVarmi == 0 ){
			
			kitapVarmiymis = 1;
		
		}else{
			
			fprintf(kitaplarSilme, "\n%s - %s - %d - %d", kitapAdi, kitapYazari, kitapFiyati[i], kitapStok[i]);
				
		}
		
	}
	
	if ( kitapVarmiymis == 1 ){
		
		printf("\n Arad���n�z kitap ad� ile uyu�an kitaplar siliniyor. \n");
		
	}else{
		
		printf("\n Arad���n�z kitap ad� ile uyu�an herhangi bir kitap bulunamad�! \n");
		
	}
	
	fclose(kitaplar);
	fclose(kitaplarSilme);
	
	remove("kitaplar.txt");
	rename("kitaplarSilme.txt","kitaplar.txt");
	
	printf("\n\n Admin paneline d�nmek i�in herhangi bir tu�a bas�n�z.");
	
	if ( getche() != 'e' ){
			
		system("cls");
		
		printf("\n Yeniden i�lem yapmak i�in Admin Giri�i yap�n.");
		
		s4_YoneticiGirisi();
		
	}
	
}
