<h1 align="center">🏰 Permainan Kelola Kerajaan 🏰</h1>

<h2 id = "description">✨ Deskripsi </h2>
Tugas Besar 01 Pemrograman Berorientasi Objek (IF2210)


<h2 id = "table-of-contents">🔍 Daftar Isi</h2>
- <a href="#description">Deskripsi</a><br/>
- <a href="#table-of-contents">Daftar Isi</a><br/>
- <a href="#contributor">Kontributor</a><br/>
- <a href="#how-to-run">Cara Penggunaan Program</a><br/>
- <a href="#feat">Fitur</a><br/>
- <a href="#structure">Struktur Folder</a>


<h2 id = "contributor">🌟Kontributor</h2>
<table>
  <tr>
    <th>Nama</th>
    <th>NIM</th>
  </tr>
  <tr>
    <th>Zidan BSA</th>
    <th>10023637</th>
  </tr>
  <tr>
    <th>Benjamin Sihombing</th>
    <th>13522054</th>
  </tr>
  <tr>
    <th>Adril Putra Merin</th>
    <th>13522068</th>
  </tr>
  <tr>
    <th>Suthasoma Mahardhika Munthe</th>
    <th>13522098</th>
  </tr>
  <tr>
    <th>Marvin Scifo Y. Hutahaean</th>
    <th>13522110</th>
  </tr>
  <tr>
    <th>Berto Richardo Togatorop</th>
    <th>13522118</th>
  </tr>
</table>


<h2 id="how-to-run">📘 Cara Penggunaan Program</h2>

### Run Program
1. Clone _repository_ ini pada _device_ dan tambahkan folder bin pada _root directory_
```bash
git clone https://github.com/BertoRichardo/IF2210_TB1_HEY
```
3. Jika Anda menggunakan _device_ berbasis UNIX seperti MacOS atau Linux, jalankan _command_ berikut pada terminal Anda
```bash
make all
```
atau
```bash
make build
make run
```
4. Untuk menghapus _file_ .o setelah menjalankan program, jalankan _command_ berikut pada terminal Anda
```bash
make clean
```


<h2 id="feat">📱Fitur</h2>

### Daftar perintah
| Perintah | Deskripsi |
| ------------- | ------------- |
| NEXT | Perintah untuk melanjutkan giliran ke pemain selanjutnya |
| CETAK_PENYIMPANAN | Mencetak penyimpanan yang dimiliki oleh pemain |
| PUNGUT_PAJAK | Perintah yang dapat digunakan oleh pemain dengan role Walikota untuk mendapatkan pajak dari pemain lainnya |
| CETAK_LADANG | Mencetak ladang yang dimiliki oleh pemain dengan role Petani |
| CETAK_PETERNAKAN | Mencetak peternakan yang dimiliki oleh pemain dengan role Peternak |
| TANAM | Menanam tanaman yang terdapat pada penyimpanan ke ladang |
| TERNAK | Menempatkan hewan yang terdapat pada penyimpanan ke peternakan |
| BANGUN | Membangun bangunan dengan menggunakan bahan-bahan yang terdapat pada penyimpanan Walikota |
| MAKAN | Memakan produk yang dapat dimakan pada penyimpanan dan menambah berat pemain |
| BERI_MAKAN | Memberi makan kepada hewan ternak pada peternakan untuk menambah berat hewan |
| BELI | Membeli barang dari toko |
| JUAL | Menjual barang ke toko |
| PANEN | Melakukan panen terhadap tanaman atau hewan yang siap dipanen dari ladang atau peternakan |
| MUAT | Memuat state pada file masukan pengguna |
| SIMPAN | Menyimpan state saat ini ke file masukan pengguna |
| TAMBAH_PEMAIN | Perintah yang dapat digunakan walikota untuk menambah pemain dengan role Petani atau Peternak |


<h2 id="structure">📁 Struktur Folder</h2>

```
│ .gitignore
│ README.md
├── bin          # berisi executable dan binary file
├── doc          # berisi laporan
├── config       # berisi config
├── state        # berisi state untuk fungsi save load
├── src
│   ├── GameObject
│   │   ├── header
│   │   └── body
│   ├── Container
│   │   ├── header
│   │   └── body
│   ├── Player
│   │   ├── header
│   │   └── body
│   ├── Shop
│   │   ├── header
│   │   └── body
│   ├── GameContext
│   │   ├── header
│   │   └── body
│   ├── GameEngine
│   │   ├── header
│   │   └── body
│   ├── Exception
│   │   ├── header
│   │   └── body
.   └── main.cpp
```
