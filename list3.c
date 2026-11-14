/* File : list3.c */
/* Deskripsi : ADT list berkait dengan representasi fisik pointer */
/* NIM & Nama : 24060125120048 & Joshua Briliant Suryana*/
/* Tanggal : 9 November 2026*/

#include <stdio.h>
#include <stdlib.h>
#include "list3.h"

/* Function Alokasi(E:infotype)->address
{mengembalikan alamat elemen E bila berhasil, Nil bila gagal} */
address Alokasi(infotype E) //representasi fisik fungsi
{	//kamus lokal
	address P;
	//algoritma
	P = (address)malloc(sizeof(Elm));
	if (P != NIL) {
		info(P) = E;
		next(P) = NIL;
		prev(P) = NIL;
	}
	return P;
}
 
/* procedure Dealokasi (input/output P:address) */ 
/* {I.S. P terdefinisi 
    F.S. P dikembalikan ke sistem  
	Proses: Melakukan pengembalian address P} */
void Dealokasi (address *P){
	//kamus lokal

	//algoritma
	if (P != NIL && *P != NIL) {
		prev(*P) = NIL;
		next(*P) = NIL;
		free(*P);
		*P = NIL;
	}
}

/* PROTOTYPE */
/********** PEMBUATAN LIST KOSONG ***********/
/* Procedure CreateList(output L:List3)
   {I.S.: - ; F.S.: L list kosong} 
   {proses: membuat list kosong}*/
void CreateList (List3 *L){
	//kamus lokal

	//algoritma
	First(*L) = NIL;
}

/****************** TEST LIST KOSONG ******************/
/* function IsEmptyList(L:List3) --> boolean 
   {mengembalikan true bila list L kosong} */
boolean IsEmptyList (List3 L){
	//kamus lokal

	//algoritma
	return (First(L) == NIL);
}

/*PENELUSURAN*/
/*procedure PrintList(input L:List3)
{I.S. L terdefinisi; F.S. :-}
{ menampilkan semua elemen list L} */
void PrintList(List3 L){
	//kamus lokal
	address P;
	//algoritma
	if (!IsEmptyList(L)) {
		P = First(L);
		while (P != NIL) {
			printf(" %c |", info(P));
			P = next(P);
		}
	} else {
		printf("List kosong");
	}
}

/*function NbElm(L:List3) --> integer
{ menghitung banyaknya elemen list L} */
int NbElm(List3 L){
	//kamus lokal
	address P;
	int total;
	//algoritma
	total = 0;
	if (!IsEmptyList(L)) {
		P = First(L);
		while (P != NIL) {
			total = total + 1;
			P = next(P);
		}
	}
	return total;
}

/******* PENAMBAHAN ELEMEN LIST ********/
/* Procedure InsertVFirst(input/output L:List3, input V:infotype )
{ I.S. List L mungkin kosong, V terdefinisi }
{ F.S. L tetap, atau bertambah elemen pertama berinfo V }
{ Insert sebuah elemen beralamat P dengan Info(P)=V sebagai elemen pertama list linier L yg mungkin kosong } */
void InsertVFirst(List3 *L, infotype V ){
	//kamus lokal
	address P;
	//algoritma
	P = Alokasi(V);
	if (P != NIL) {
		if (!IsEmptyList(*L)) {
			next(P) = First(*L);
			prev(First(*L)) = P;
			First(*L) = P;
		} else {
			First(*L) = P;
		}
	}
}

/*Procedure InsertVLast(input/output L:List3, input V:infotype )
{ I.S. List L mungkin kosong, V terdefinisi }
{ F.S. L tetap, atau bertambah elemen terakhir berinfo V}
{ Insert sebuah elemen beralamat P dengan Info(P)=V sebagai elemen akhir list linier L yg mungkin kosong }*/
void InsertVLast(List3 *L, infotype V ){
	//kamus lokal
	address P, Q;
	//algoritma
	P = Alokasi(V);
	if (P != NIL) {
		if (!IsEmptyList(*L)) {
			Q = First(*L);
			while (next(Q) != NIL) {
				Q = next(Q);
			}
			next(Q) = P;
			prev(P) = Q;
		} else {
			First(*L) = P;
		}
	}
}

/******* PENGHAPUSAN ELEMEN ********/
/*Procedure DeleteVFirst(input/output L:List3, output V:infotype )
{ I.S. List L tidak kosong }
{ F.S. Elemen pertama list L dihapus, dan didealokasi. Hasil penghapusan disimpan nilainya dalam V. Default V='#'.
List mungkin menjadi kosong. Jika tidak kosong, elemen pertama list yang baru adalah elemen sesudah elemen pertama yang lama. } */
void DeleteVFirst(List3 *L, infotype *V){
	//kamus lokal
	address P;
	//algoritma
	*V = '#';
	if (!IsEmptyList(*L)) {
		P = First(*L);
		*V = info(P);
		if (next(P) == NIL) { // ketika 1 elemen
			First(*L) = NIL;
		} else { // ketika lebih dari 1 elemen
			First(*L) = next(P);
			prev(First(*L)) = NIL;
		}
		Dealokasi(&P);
	}
}

/*Procedure DeleteVLast(input/output L:List3, output V:infotype )
{ I.S. List L terdefinisi }
{ F.S. Elemen terakhir list L dihapus, dan didealokasi. Hasil penghapusan disimpan nilainya dalam V. Default V='#'.
List mungkin menjadi kosong. Jika tidak kosong, elemen terakhir list yang baru adalah elemen sebelum elemen terakhir yang lama. }*/
void DeleteVLast(List3 *L, infotype *V){
	//kamus lokal
	address P;
	//algoritma
	*V = '#';
	if (!IsEmptyList(*L)) {
		P = First(*L);
		if (next(P) == NIL) { // ketika 1 elemen
			*V = info(P);
			First(*L) = NIL;
		} else { // ketika lebih dari 1 elemen
			while (next(P) != NIL) {
				P = next(P);
			}
			*V = info(P);
			next(prev(P)) = NIL;
		}
		Dealokasi(&P);
	}
}

/*Procedure DeleteX(input/output L:List3, input X:infotype)
{ I.S. List L terdefinisi }
{ F.S. List mungkin menjadi kosong, atau berkurang 1 elemen. }
{ Proses: Elemen bernilai X dihapus, dan didealokasi. }*/
void DeleteX(List3 *L, infotype X){
	//kamus lokal
	address P;
	//algoritma
	if (!IsEmptyList(*L)) {
		P = First(*L);
		while (P != NIL && info(P) != X) {
			P = next(P);
		}
		if (P != NIL) { // elemen X ditemukan
			if (P == First(*L)) { // elemen di awal
				First(*L) = next(P);
				if (First(*L) != NIL) {
					prev(First(*L)) = NIL;
				}
			} else { // elemen di tengah atau akhir
				next(prev(P)) = next(P);
				if (next(P) != NIL) {
					prev(next(P)) = prev(P);
				}
			}
			Dealokasi(&P);
		}
	}
}

/*** PENCARIAN ***/
/*Procedure SearchX(input L:List3, input X:infotype, output A:address )
{ I.S. L, X terdefinisi }
{ F.S. A berisi alamat elemen yang nilainya X. }
{ Proses : Mencari apakah ada elemen list dengan info(P)= X. Jika ada, mengisi A dengan address elemen tersebut. Jika tidak ada, A=Nil }*/
void SearchX(List3 L, infotype X, address *A){
	//kamus lokal
	address P;
	//algoritma
	*A = NIL;
	if (!IsEmptyList(L)) {
		P = First(L);
		while (P != NIL && info(P) != X) {
			P = next(P);
		}
		*A = P;
	}
}

/*** MANIPULASI ELEMEN LIST ***/
/*Procedure UpdateX(input/output L:List3, input X:infotype, input Y:infotype)
{ I.S. L, X, Y terdefinisi }
{ F.S. L tetap, atau elemen bernilai X berubah menjadi Y.}
{ Proses : Mengganti elemen bernilai X menjadi bernilai Y}*/
void UpdateX(List3 *L, infotype X, infotype Y){
	//kamus lokal
	address P;
	//algoritma
	if (!IsEmptyList(*L)) {
		SearchX(*L, X, &P);
		if (P != NIL) {
			info(P) = Y;
		}
	}
}

/*Procedure Invers(input/output L:List3)
{ I.S. L terdefinisi }
{ F.S. urutan posisi elemen terbalik, misal {3,5,6} menjadi {6,5,3} }*/
void Invers(List3 *L){
	//kamus lokal
	address P, temp;
	//algoritma
	if (!IsEmptyList(*L)) {
		P = First(*L);
		while (P != NIL) {
			// Simpan next lama
			temp = next(P);
			// Tukar pointer next dan prev
			next(P) = prev(P);
			prev(P) = temp;
			// Jika elemen terakhir list lama, jadikan First baru
			if (temp == NIL) {
				First(*L) = P;
			}
			// Geser P maju ke elemen berikutnya
			P = temp;
		}
	}
}

/*********** SOAL TAMBAHAN, DIKERJAKAN BILA LUANG *****************/
/*Procedure InsertVAfterX(input/output L:List3, input X:infotype, input V:infotype )
{ I.S. List L mungkin kosong }
{ F.S. P dialokasi, Info(P)=V }
{ Insert sebuah elemen beralamat P dengan Info(P)=V sebagai elemen dengan posisi setelah elemen bernilai X }*/
void InsertVAfterX(List3 *L, infotype X, infotype V){
	//kamus lokal
	address P, T;
	//algoritma
	if (!IsEmptyList(*L)) {
		SearchX(*L, X, &P);
		if (P != NIL) {
			T = Alokasi(V);
			if (T != NIL) {
				next(T) = next(P);
				prev(T) = P;
				if (next(P) != NIL) {
					prev(next(P)) = T;
				}
				next(P) = T;
			}
		}
	}
}

/*Procedure InsertVBeforeX(input/output L:List3, input X:infotype, input V:infotype )
{ I.S. List L mungkin kosong }
{ F.S. P dialokasi, Info(P)=V }
{ Insert sebuah elemen beralamat P dengan Info(P)=V sebagai elemen dengan posisi sebelum elemen bernilai X }*/
void InsertVBeforeX(List3 *L, infotype X, infotype V){
	//kamus lokal
	address P, T;
	//algoritma
	if (!IsEmptyList(*L)) {	
		SearchX(*L, X, &P);
		if (P != NIL) {
			if (P == First(*L)) {
				InsertVFirst(L, V);
			} else {
				T = Alokasi(V);
				if (T != NIL) {
					next(T) = P;
					prev(T) = prev(P);
					next(prev(P)) = T;
					prev(P) = T;
				}
			}
		}
	}
}

/*Procedure DeleteVAfterX(input/output L:List3, input X:infotype, output V:infotype )
{ I.S. List L tidak kosong }
{ F.S. Elemen setelah X dihapus, dan didealokasi. Hasil penghapusan disimpan nilainya dalam V.
List mungkin menjadi kosong. }*/
void DeleteVAfterX(List3 *L, infotype X, infotype *V){
	//kamus lokal
	address P, Q;
	//algoritma
	*V = '#';
	if (!IsEmptyList(*L)) {
		SearchX(*L, X, &P);
		if (P != NIL && next(P) != NIL) {
			Q = next(P);
			*V = info(Q);
			next(P) = next(Q);
			if (next(Q) != NIL) {
				prev(next(Q)) = P;
			}
			Dealokasi(&Q);
		}
	}
}

/*Procedure DeleteVBeforeX(input/output L:List3, input X:infotype, output V:infotype )
{ I.S. List L tidak kosong }
{ F.S. Elemen sebelum X dihapus, dan didealokasi. Hasil penghapusan disimpan nilainya dalam V.
List mungkin menjadi kosong. }*/
void DeleteVBeforeX(List3 *L, infotype X, infotype *V){
	//kamus lokal
	address P, Q;
	//algoritma
	*V = '#';
	if (!IsEmptyList(*L)) {
		SearchX(*L, X, &P);
		if (P != NIL && prev(P) != NIL) {
			Q = prev(P);
			*V = info(Q);
			if (Q == First(*L)) {
				First(*L) = P;
				prev(P) = NIL;
			} else {
				next(prev(Q)) = P;
				prev(P) = prev(Q);
			}
			Dealokasi(&Q);
		}
	}
}

/*function CountX(L:List3, X:infotype) -> integer */
/*{ mengembalikan banyaknya kemunculan X dalam list L}*/
int CountX(List3 L, infotype X){
	//kamus lokal
	address P;
	int total;
	//algoritma
	total = 0;
	if (!IsEmptyList(L)) {
		P = First(L);
		while (P != NIL) {
			if (info(P) == X) {
				total = total + 1;
			}
			P = next(P);
		}
	}
	return total;
}

/*function FrekuensiX(L:List3, X:infotype) -> real */
/*{ mengembalikan rasio kemunculan X dibandingkan ukuran list L }*/
float FrekuensiX(List3 L, infotype X){
	//kamus lokal
	int jml, total;
	//algoritma
	total = NbElm(L);
	if (total > 0) {
		jml = CountX(L, X);
		return ((float)jml / (float)total);
	} else {
		return 0.0f;
	}
}

/*function MaxMember(L:List3) -> integer */
/*{ mengembalikan banyaknya huruf yang paling banyak muncul di list L}*/
int MaxMember(List3 L){
	//kamus lokal
	address P;
	int maks, c;
	//algoritma
	maks = 0;
	if (!IsEmptyList(L)) {
		P = First(L);
		while (P != NIL) {
			c = CountX(L, info(P));
			if (c > maks) {
				maks = c;
			}
			P = next(P);
		}
	}
	return maks;
}

/*function Modus(L:List3) -> character */
/*{ mengembalikan huruf yang paling banyak muncul dalam list L}*/
char Modus(List3 L){
	//kamus lokal
	address P;
	char modus;
	int maks, c;
	//algoritma
	modus = '#';
	maks = 0;
	if (!IsEmptyList(L)) {
		P = First(L);
		while (P != NIL) {
			c = CountX(L, info(P));
			if (c > maks) {
				maks = c;
				modus = info(P);
			}
			P = next(P);
		}
	}
	return modus;
}

/*function CountVocal(L:List3) -> integer */
/*{ mengembalikan banyaknya kemunculan huruf vokal dalam list L}*/
int CountVocal(List3 L){
	//kamus lokal
	address P;
	int total;
	char c;
	//algoritma
	total = 0;
	if (!IsEmptyList(L)) {
		P = First(L);
		while (P != NIL) {
			c = info(P);
			if (c == 'A' || c == 'a' || c == 'I' || c == 'i' ||
			    c == 'U' || c == 'u' || c == 'E' || c == 'e' ||
			    c == 'O' || c == 'o') {
				total = total + 1;
			}
			P = next(P);
		}
	}
	return total;
}

/*function CountNG(L:List3) -> integer */
/*{ mengembalikan banyaknya huruf N yang langsung diikuti huruf G dalam list L}*/
int CountNG(List3 L){
	//kamus lokal
	address P;
	int total;
	//algoritma
	total = 0;
	if (!IsEmptyList(L)) {
		P = First(L);
		while (P != NIL && next(P) != NIL) {
			if ((info(P) == 'N' || info(P) == 'n') && (info(next(P)) == 'G' || info(next(P)) == 'g')) {
				total = total + 1;
			}
			P = next(P);
		}
	}
	return total;
}

/*Procedure SearchAllX(input L:List3, input X:infotype)
{ I.S. L, X terdefinisi }
{ F.S. - }
{ Proses: menampilkan posisi-posisi kemunculan elemen X dalam list L }*/
/*misal L=['M','A','N','D','A'], SearchAllX(L,'A') menampilkan angka 2,5 */
/*misal L=['M','A','N','D','A'], SearchAllX(L,'J') menampilkan angka 0 */
void SearchAllX(List3 L, infotype X){
	//kamus lokal
	address P;
	int pos;
	boolean temu;
	//algoritma
	pos = 1;
	temu = false;
	if (!IsEmptyList(L)) {
		P = First(L);
		while (P != NIL) {
			if (info(P) == X) {
				if (temu) {
					printf(",%d", pos);
				} else {
					printf("%d", pos);
					temu = true;
				}
			}
			pos = pos + 1;
			P = next(P);
		}
		if (!temu) {
			printf("0");
		}
	} else {
		printf("0");
	}
}

/*Procedure DeleteAllX(input/output L:List3, input X:infotype)
{ I.S. List L tidak kosong }
{ F.S. List mungkin menjadi kosong. }
{ Proses: Semua elemen bernilai X dihapus, dan didealokasi. }*/
void DeleteAllX(List3 *L, infotype X){
	//kamus lokal
	address A;
	//algoritma
	if (!IsEmptyList(*L)) {
		SearchX(*L, X, &A);
		while (A != NIL && !IsEmptyList(*L)) {
			DeleteX(L, X);
			SearchX(*L, X, &A);
		}
	}
}

/*OPERASI BANYAK LIST*/
/*Procedure ConcatList(input L1:List3, input L2:List3, output L:List3)
{I.S.: L1,L2 terdefinisi ; 
 F.S.: L gabungan L1 dan L2}*/
void ConcatList(List3 L1, List3 L2, List3 *L){
	//kamus lokal
	address P;
	//algoritma
	CreateList(L);
	if (IsEmptyList(L1)) {
		if (!IsEmptyList(L2)) {
			First(*L) = First(L2);
		}
	} else {
		First(*L) = First(L1);
		if (!IsEmptyList(L2)) {
			P = First(L1);
			while (next(P) != NIL) {
				P = next(P);
			}
			next(P) = First(L2);
			prev(First(L2)) = P;
		}
	}
}

/*Procedure SplitList(input L:List3, output L1:List3, output L2:List3)
{I.S.: L terdefinisi ; 
 F.S.: L1, L2 hasil pemecahan L}*/
void SplitList(List3 L, List3 *L1, List3 *L2){
	//kamus lokal
	address P;
	int n, k, i;
	//algoritma
	CreateList(L1);
	CreateList(L2);
	if (!IsEmptyList(L)) {
		n = NbElm(L);
		k = (n + 1) / 2; // kelebihan 1 elemen masuk ke L1
		P = First(L);
		i = 1;
		while (i < k) {
			P = next(P);
			i = i + 1;
		}
		// P menunjuk elemen ke-k (elemen terakhir L1)
		First(*L1) = First(L);
		First(*L2) = next(P);
		if (First(*L2) != NIL) {
			prev(First(*L2)) = NIL;
		}
		next(P) = NIL;
	}
}

/*Procedure CopyList(input L1:List3, output L2:List3)
{I.S.: L1 terdefinisi;  
 F.S.: L2 menjadi salinan L1}*/
void CopyList(List3 L1, List3 *L2){
	//kamus lokal
	address P;
	//algoritma
	CreateList(L2);
	if (!IsEmptyList(L1)) {
		P = First(L1);
		while (P != NIL) {
			InsertVLast(L2, info(P));
			P = next(P);
		}
	}
}
