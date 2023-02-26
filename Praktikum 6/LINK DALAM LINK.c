/*  NAMA ANGGOTA    : BANTENG HARISANTOSO   (221524036)
    KELAS           : 1B-TI4
    PROGRAM         : PROGRAM UNTUK MEMBUAT ARRAY OF LINKED LIST KOTA DAN MAHASISWA
    TANGGAL         : 20 JANUARI 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*============================STRUKTUR DATA ============================*/
//STRUKTUR DATA UNTUK BARIS KOTA
typedef struct{
    char kota[15];
} Kota;

//STRUKTUR DATA UNTUK KOLOM MAHASISWA
typedef struct{
    char nama[15];
}mahasiswa;

//STRUKTUR DATA UNTUK ELEMEN KOLOM
typedef struct eklm* alamatekolom;
typedef struct eklm{
    mahasiswa kontainer_kol;
    alamatekolom next_kol;
}eKolom;

//STRUKTUR DATA UNTUK ELEMEN BARIS
typedef struct ebr* alamatebaris;
typedef struct ebr{
    Kota kontainer;
    eKolom *col;
    alamatebaris next;
}eBaris;

//STRUKTUR DATA UTAMA
typedef struct{
    eBaris *first;
}list;

/*============================ MODULAR ============================*/
void createList(list *L)
/*  DESKRIPSI   : Prosedur untuk membuat list baru
    IS          : List belum ada
    FS          : List sudah dibentuk dengan nilai NULL
*/
{
    (*L).first = NULL;
}

void AddFirstB(char kota[], list *L)
/*  DESKRIPSI   : Prosedur untuk menambahkan data nama kota ke Baris
    IS          : Sudah ada list terbentuk
    FS          : Node baru ditambahkan dengan data nama kota serta dua pointer yang menujuk ke eBaris dan eKolom
*/
{
    eBaris *baru;
    baru = (eBaris *) malloc (sizeof(eBaris));
    strcpy(baru->kontainer.kota, kota);
    baru->col = NULL;

    if((*L).first == NULL){
        baru->next = NULL;
    }
    else{
        baru->next = (*L).first;
    }

    (*L).first = baru;
    baru = NULL;
    
}

void AddAfterB(eBaris *prev, char kota[])
/*  DESKRIPSI   : Prosedur untuk menambahkan data nama kota di tengah baris
    IS          : Sudah ada list terbentuk dan sudah ada elemen pertama
    FS          : Node baru ditambahkan yang berada sesudah elemen baris prev
*/
{
    if(prev != NULL){
        eBaris *baru;
        baru = (eBaris *) malloc (sizeof(eBaris));
        strcpy(baru->kontainer.kota, kota);
        baru->col = NULL;

        if(prev->next == NULL){
            baru->next = NULL;
        }
        else{
            baru->next = prev->next;
        }
        prev->next = baru;
        baru = NULL;
    }
    
}

void AddLastB(char kota[], list *L)
/*  DESKRIPSI   : Prosedur untuk menambahkan data nama kota di akhir baris
    IS          : Sudah ada list terbentuk dan sudah ada elemen pertama
    FS          : Node baru ditambahkan yang berada di akhir baris
*/
{
    if((*L).first == NULL){
        AddFirstB(kota, L);
    }
    else{
        eBaris *last = (*L).first;
        
        while(last->next != NULL){
            last = last->next;
        }
        AddAfterB(last, kota);
    }
}

void AddFirstK(char nama[], eBaris *L)
/*  DESKRIPSI   : Prosedur untuk menambahkan data nama mahasiswa ke Kolom
    IS          : Sudah ada list dan node Baris yang terbentuk
    FS          : Node baru ditambahkan di kota sebagai elemen pertama
*/
{
    eKolom *baru;
    baru = (eKolom *) malloc (sizeof(eKolom));
    strcpy(baru->kontainer_kol.nama, nama);

    if((*L).col == NULL){
        baru->next_kol = NULL;
    }
    else{
        baru->next_kol = (*L).col;
    }
    (*L).col = baru;
    baru = NULL;
}

void AddAfterK(eKolom *prev, char nama[])
/*  DESKRIPSI   : Prosedur untuk menambahkan data nama kota di tengah kolom
    IS          : Sudah ada list terbentuk dan sudah ada elemen pertama
    FS          : Node baru ditambahkan yang berada sesudah elemen kolom prev
*/
{
    if(prev != NULL){
        eKolom *baru;
        baru = (eKolom *) malloc (sizeof(eKolom));
        strcpy(baru->kontainer_kol.nama, nama);

        if(prev->next_kol == NULL){
            baru->next_kol = NULL;
        }
        else{
            baru->next_kol = prev->next_kol;
        }
        prev->next_kol = baru;
        baru = NULL;
    }
    
}

void AddLastK(char nama[], eBaris *L)
/*  DESKRIPSI   : Prosedur untuk menambahkan data nama kota di akhir kolom
    IS          : Sudah ada list terbentuk dan sudah ada elemen pertama
    FS          : Node baru ditambahkan yang berada di akhir kolom
*/
{
    if((*L).col == NULL){
        AddFirstK(nama, L);
    }
    else{
        eKolom *last = (*L).col;
        while(last->next_kol != NULL){
            last = last->next_kol;
        }
        AddAfterK(last, nama);
    }
    
}


void printElemen(list L)
/*  DESKRIPSI   : Prosedur untuk menampilkan kota dan nama mahasiswa yang berasal dari kota tersebut
    IS          : Sudah terbentuk list beserta node-nodenya yang saling terhubung
    FS          : Ditampilkan list Kota dan Mahasiswa
*/
{

    
    if(L.first != NULL){

        eBaris *bantu = L.first;

        while(bantu != NULL){
            printf("Kota %s: ", bantu->kontainer.kota);

            eKolom *bantu_kol = bantu->col;
            while(bantu_kol != NULL){
                printf("%s ", bantu_kol->kontainer_kol.nama);
                bantu_kol = bantu_kol->next_kol;
            }
            printf("\n");
            bantu = bantu->next;
        }
    }
    else{
        printf("List kosong!\n");
    }
}

/*============================ PROGRAM UTAMA ============================*/
int main(){
    list L;
    createList(&L);

    //BANDUNG
    AddFirstB("Bandung", &L);
    AddFirstK("Hari", L.first);
    AddAfterK(L.first->col, "Daffa");
    AddLastK("Fahri", L.first);

    //CIMAHI
    AddAfterB(L.first, "Cimahi");
    AddFirstK("Fathur", L.first->next); 
    AddLastK("Niqa", L.first->next);
    AddAfterK(L.first->next->col->next_kol, "Alisha");

    ////KBB
    AddLastB("Kabupaten", &L);
    AddFirstK("Taqin", L.first->next->next);
    AddAfterK(L.first->next->next->col, "Jeihan");
    AddLastK("Zahran", L.first->next->next);

    printElemen(L);
}
