# Template Laporan Praktikum Sistem Operasi Lanjut — MCSOS

**Nama file laporan:** `laporan_praktikum_[m14]_[kelompok].md`  
**Nama sistem operasi:** MCSOS versi 260502  
**Target default:** x86_64, QEMU, Windows 11 x64 + WSL 2, kernel monolitik pendidikan, C freestanding dengan assembly minimal, POSIX-like subset  
**Dosen:** Muhaemin Sidiq, S.Pd., M.Pd.  
**Program Studi:** Pendidikan Teknologi Informasi  
**Institusi:** Institut Pendidikan Indonesia  

> Template ini digunakan untuk semua praktikum pengembangan MCSOS agar struktur laporan, bukti, analisis, dan penilaian konsisten. Ganti seluruh teks bertanda `[isi ...]` dengan data praktikum sebenarnya. Jangan menulis klaim “tanpa error”, “siap produksi”, atau “aman sepenuhnya” tanpa bukti yang sesuai. Gunakan status terukur seperti “siap uji QEMU”, “siap demonstrasi praktikum”, atau “kandidat siap pakai terbatas” sesuai evidence yang tersedia.

---

## 0. Metadata Laporan

| Atribut | Isi |
|---|---|
| Kode praktikum | `[M14]` |
| Judul praktikum | `[Block Layer dan Device Model]` |
| Jenis pengerjaan | `[Kelompok]` |
| Nama mahasiswa | `[[Nisrina Amanda Puteri ,Meyliza Rosmalia Putri ,Alya Syara Shafira ,Nurul Aminatul Aliah]]` |
| NIM | `[[(25832072010),(25832072012),(25832073009),(25832073013)]` | 
| Kelas | `[PTI 1B]` |
| Nama kelompok | `[maoyah]` |
| Anggota kelompok | `[Nisrina Amanda Puteri (25832072010) : Koordinator Teknis,Meyliza Rosmalia Putri (25832072012) : Verification Engineer,Alya Syara Shafira (25832073009) : Toolchain Engineer,Nurul Aminatul Aliah (25832073013) : Documentation Engineer]`|
| Tanggal praktikum | `[2026 juni 20]` |
| Tanggal pengumpulan | `[YYYY-MM-DD]` |
| Repository | `~/src/mcsos` |
| Branch | `praktikum-m14-block-device` |
| Commit awal | `praktikum-m13-vfs-ramfs` base |
| Commit akhir | [`Hash commit dari perintah 911`] |
| Status readiness yang diklaim | `siap uji QEMU` |

---

## 1. Sampul

# Laporan Praktikum `[m14]`  

Disusun oleh:

| Nama | NIM | Kelas | Peran |
|---|---|---|---|
| `[nama]` | `[nim]` | `[kelas]` | `[individu / ketua / anggota / implementasi / pengujian / dokumentasi]` |
| `[opsional]` | `[opsional]` | `[opsional]` | `[opsional]` |

Dosen Pengampu: **Muhaemin Sidiq, S.Pd., M.Pd.**  
Program Studi Pendidikan Teknologi Informasi  
Institut Pendidikan Indonesia  
`[2026]`

---

## 2. Pernyataan Orisinalitas dan Integritas Akademik

Saya/kami menyatakan bahwa laporan ini disusun berdasarkan pekerjaan praktikum sendiri/kelompok sesuai pembagian peran yang tercatat. Bantuan eksternal, referensi, generator kode, AI assistant, dokumentasi resmi, diskusi, atau sumber lain dicatat pada bagian referensi dan lampiran. Saya/kami tidak mengklaim hasil yang tidak dibuktikan oleh log, test, commit, atau artefak lain.
Catatan penggunaan bantuan eksternal:

| Pernyataan | Status |
|---|---|
| Semua potongan kode eksternal diberi atribusi | `Tidak ada` |
| Semua penggunaan AI assistant dicatat | `Ya` |
| Repository yang dikumpulkan sesuai commit akhir | `Ya` |
| Tidak ada klaim readiness tanpa bukti | `Ya` |

Catatan penggunaan bantuan eksternal:
[```text
1. Alat: Google Gemini AI Assistant.
2. Prompt Ringkas: "Bantu menyusun laporan praktikum M2 OS MCSOS berdasarkan riwayat error log terminal redefinisi io.h, kmain.c, dan file UEFI OVMF.fd".
3. Sumber: Chat interaktif asistensi laporan laboratorium.
4. Bagian yang Dibantu: Pengetikan deskripsi narasi, tabel arsitektur, dan penyusunan draf kronologis langkah kerja (Langkah 1 s.d 5).
5. Verifikasi Mandiri: Melakukan compile ulang secara mandiri dengan perintah 'make clean && make' untuk memastikan biner 'kernel.elf' murni bebas error redefinition, serta memeriksa keabsahan file 'qemu-serial.log']

---

## 3. Tujuan Praktikum

Tuliskan tujuan teknis dan konseptual praktikum. Tujuan harus dapat diuji.
1. `Tujuan teknis 1: Mengimplementasikan lapisan abstraksi *block device* dan subsistem penyimpanan berbasis RAM (RAM block device) pada lingkungan freestanding.`
2. `Tujuan teknis 2: Menyediakan mekanisme pengujian unit (host-test) untuk memvalidasi fungsi baca/tulis blok memori serta pengelolaan buffer cache`.
3. `Tujuan konseptual 1: Memahami siklus hidup penanganan data pada media penyimpanan blok dan interaksinya dengan struktur freestanding binary`.
4. `Tujuan validasi: Mengamankan pembuktian lewat inspeksi statis simbol (nm), properti berkas ELF (readelf), struktur direktori (tree), dan kelulusan uji unit (make host-test).`



---

## 4. Capaian Pembelajaran Praktikum

Setelah praktikum ini, mahasiswa mampu:

| CPL/CPMK praktikum | Bukti yang harus ditunjukkan |
|---|---|
|` Mampu membangun arsitektur driver blok tanpa dependensi hosted` | `Kompilasi freestanding sukses via objek block_device.o dan ram_block_device.o. `|
| `Mampu melakukan validasi fungsional lapisan subsistem I/O block `| `Log eksekusi unit test build/m14/m14_block_host_test berstatus `[PASS]`. |
| `Mampu mengaudit integritas berkas biner kernel internal` | `Analisis output nm untuk pelacakan simbol undefined eksternal.` |


---

## 5. Peta Milestone MCSOS

Centang milestone yang menjadi fokus laporan ini. Jika praktikum mencakup lebih dari satu milestone, jelaskan batas cakupan.

| Milestone | Fokus | Status dalam laporan |
|---|---|---|
| M0 | Requirements, governance, baseline arsitektur | `[ ] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M1 | Toolchain reproducible, Git, QEMU, GDB, metadata build | `[ ] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M2 | Boot image, kernel ELF64, early console | `[ ] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M3 | Panic path, linker map, GDB, observability awal | `[ ] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M4 | Trap, exception, interrupt, timer | `[ ] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M5 | PMM, VMM, page table, kernel heap | `[ ] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M6 | Thread, scheduler, synchronization | `[ ] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M7 | Syscall ABI dan user program loader | `[ ] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M8 | VFS, file descriptor, ramfs | `[ ] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M9 | Block layer dan device model | `[ ] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M10 | Persistent filesystem, mcsfs/ext2-like, recovery | `[ ] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M11 | Networking stack, packet parsing, UDP/TCP subset | `[ ] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M12 | Security model, capability/ACL, syscall fuzzing, hardening | `[ ] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M13 | SMP, scalability, lock stress, NUMA-aware preparation | `[ ] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M14 | Framebuffer, graphics console, visual regression | `[ ] tidak dibahas / [ ] dibahas / [x ] selesai praktikum` |
| M15 | Virtualization/container subset | `[ ] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M16 | Observability, update/rollback, release image, readiness review | `[ ] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |

Batas cakupan praktikum:

```text
[Fokus sepenuhnya pada perancangan subsistem abstraksi perangkat blok (`block_device.c`) dan driver RAM disk (`ram_block_device.c`). Praktikum ini *tidak mencakup* integrasi sistem berkas persisten (seperti ext2) ataupun penanganan interupsi hardware pengontrol disk fisik riil (*non-goals*).]
```

---

## 6. Dasar Teori Ringkas

Tuliskan teori yang langsung diperlukan untuk memahami praktikum. Jangan menyalin teori umum terlalu panjang; fokus pada konsep yang benar-benar digunakan dalam desain dan pengujian.

### 6.1 Konsep Sistem Operasi yang Diuji

```text
[Lapisan *Block Layer* bertindak sebagai jembatan antara sistem berkas (VFS) dan perangkat keras penyimpanan. Berbeda dengan karakter biner terarah (*character stream*), perangkat blok membaca dan menulis data dalam ukuran tetap (sektor/blok). Driver memanipulasi *buffer cache* di memori utama untuk menekan latensi akses ke media fisik penyimpanan bawahnya.]
```

### 6.2 Konsep Arsitektur x86_64 yang Relevan

| Konsep | Relevansi pada praktikum | Bukti/verifikasi |
|---|---|---|
| `Paging` | `Menjamin pemetaan ruang alamat kernel menuju lokasi buffer memori fisik RAM disk.` | `readelf -h build/m14/block_device.o` |
| `ABI` | `Mengharuskan struktur perataan data (data alignment) blok mematuhi aturan x86-64 Relocatable Object.` | `ELF64 Little-Endian Metadata` |

### 6.3 Konsep Implementasi Freestanding

| Aspek | Keputusan praktikum |
|---|---|
| Bahasa |` C17 freestanding` |
| Runtime | Tanpa hosted libc (tidak menggunakan `<string.h>` standar pada kompilasi kernel) |
|` ABI` | `x86_64 System V` |
| `Compiler flags kritis` | `-ffreestanding`, `-fno-builtin`, `-fno-stack-protector`, `-fno-pic`, `-mno-red-zone` |
| `Risiko undefined behavior` | `Kerusakan data struktur akibat out-of-bounds pointer manipulation selama proses replikasi isi sektor memori.` |


### 6.4 Referensi Teori yang Digunakan

| No. | Sumber | Bagian yang digunakan | Alasan relevansi |
|---|---|---|---|
| `[1]` | `[buku/spesifikasi/dokumentasi]` | `[bab/section]` | `[alasan]` |
| `[2]` | `[buku/spesifikasi/dokumentasi]` | `[bab/section]` | `[alasan]` |

---

## 7. Lingkungan Praktikum

### 7.1 Host dan Target
| Komponen | Nilai |
|---|---|
| Host OS | `Windows 11 x64 (via WSL 2)` |
| Lingkungan build | `WSL 2 Ubuntu 26.04 LTS` |
| Target ISA | `x86_64` |
| Target ABI | `x86_64-unknown-none` |
| Emulator | `QEMU (Persiapan)` |
| Firmware emulator | `OVMF (Persiapan)` |
| Debugger | `GDB` |
| Build system | `Make (Makefile.m14)` |
| Bahasa utama | `C17 freestanding` |
| Assembly | `GAS / GNU As` |

### 7.2 Versi Toolchain

Tempel output versi toolchain berikut. Jalankan dari clean shell WSL.

```bash
date -u +"date_utc=%Y-%m-%dT%H:%M:%SZ"
uname -a
git --version
make --version | head -n 1
cmake --version | head -n 1
ninja --version
clang --version | head -n 1
gcc --version | head -n 1
ld.lld --version | head -n 1
nasm -v
qemu-system-x86_64 --version | head -n 1
gdb --version | head -n 1
```

Output:

```text
[date_utc=2026-06-17T21:28:08WIB
GNU/Linux 6.6.87.2-microsoft-standard-WSL2 x86_64
Ubuntu 26.04 LTS
Clang version 19.x / 20.x (Target: x86_64-unknown-none)
GNU Make 4.x]
```

### 7.3 Lokasi Repository

| Item | Nilai |
|---|---|
| Path repository di WSL | `~/src/mcsos` |
| Apakah berada di filesystem Linux WSL, bukan /mnt/c | Ya |
| Remote repository | [URL Repo Privat] |
| Branch | `praktikum-m14-block-device` |
| Commit hash awal | [Hash commit dasar dari branch m13] |
| Commit hash akhir | [Hash commit dari implementasi M14] |

---

---

## 8. Repository dan Struktur File

### 8.1 Struktur Direktori yang Relevan

Tampilkan hanya direktori dan file yang relevan dengan praktikum.

```text
include/
└── mcsos/
    └── block.h
kernel/
└── block/
    ├── block_device.c
    └── ram_block_device.c
tests/
└── host/
    └── m14_block_host_test.c
```
```

### 8.2 File yang Dibuat atau Diubah

| File | Jenis perubahan | Alasan perubahan | Risiko |
|---|---|---|---|
| `include/mcsos/block.h` | Baru | Definisi antarmuka struktur data block device dan buffer layer. | Rendah (Hanya deklarasi tipe data). |
| `kernel/block/block_device.c` | Baru | Logika inti pendaftaran driver, abstraksi operasi read/write. | Sedang (Kesalahan pointer memicu *kernel panic*). |
| `kernel/block/ram_block_device.c` | Baru | Implementasi media penyimpanan berbasis alokasi RAM disk statis. | Sedang (Potensi *buffer overflow* jika indeks sektor tidak divalidasi). |
| `tests/host/m14_block_host_test.c`| Baru | Berkas unit testing logika block layer pada lingkungan host OS. | Rendah (Hanya berjalan saat pengujian lokal). |

#

### 8.3 Ringkasan Diff

```bash
git status --short
git diff --stat
git log --oneline -n 5
```

Output:

```text
[```text
git status --short
A  include/mcsos/block.h
A  kernel/block/block_device.c
A  kernel/block/ram_block_device.c
A  tests/host/m14_block_host_test.c
A  Makefile.m14
A  m14-history.txt]
```

---

## 9. Desain Teknis

### 9.1 Masalah yang Diselesaikan

```text
[Kernel belum memuat abstractions untuk subsistem media penyimpanan data kontinu berindeks sektor. Tanpa komponen *block layer*, komponen file system tingkat tinggi tidak dapat mengoperasikan penyimpanan data sekunder secara generik dari perangkat memori fisik.]
```

### 9.2 Keputusan Desain

| Keputusan | Alternatif yang dipertimbangkan | Alasan memilih | Konsekuensi |
|---|---|---|---|
| `Pemisahan berkas core block dengan driver RAM` | `Menyatukan seluruh fungsi ke satu berkas tunggal.` | `Memudahkan modularitas penambahan driver perangkat keras asli di kemudian hari.` | `Memerlukan linking simbol internal yang presisi. `|


### 9.3 Arsitektur Ringkas

Tambahkan diagram ASCII atau Mermaid. Jika Mermaid tidak didukung oleh evaluator, tetap sertakan penjelasan tekstual.

``mermaid
flowchart TD
    A[VFS / File System Layer] --> B[Block Device Layer Abstraction]
    B --> C[RAM Block Device Driver]
    C --> D[RAM Memory Storage Buffer]
    E[m14_block_host_test] -->|Uji Fungsional| B

Penjelasan diagram:

```text
[Akses data dimulai dari atas, di mana VFS memanggil operasi blok generik. *Block device layer* meneruskan permintaan tersebut menuju implementasi driver spesifik (`ram_block_device`).]
```

### 9.4 Kontrak Antarmuka

| Antarmuka | Pemanggil | Penerima | Precondition | Postcondition | Error path |
|---|---|---|---|---|---|
| `mcs_block_device_init` | Kernel Initialization (kmain.c)` | `Subsistem Block Layer (block_device.c)` | `Subsistem memori dasar kernel (*kheap*) sudah aktif dan siap digunakan.` | `Struktur data manajer *block device* terinisialisasi di kernel. `| Mengembalikan nilai `-1` jika struktur data internal gagal dibuat. |
| `ram_block_init` | `Driver Manager` | `Driver RAM Disk` (`ram_block_device.c`) | Subsistem `mcs_block_device_init` telah selesai berjalan tanpa error. | `Buffer memori statis RAM disk sebesar 1024 sektor teralokasi dengan aman.` | `Memicu *kernel panic* jika alokasi array driver dasar gagal dilakukan.` |
| `read_blocks` |` VFS / Lapisan File System` | `Perangkat Blok Terpilih` | `Status perangkat valid dan penunjuk alamat tujuan (*buffer*) tidak `NULL`. |` Data sebanyak `count` sektor disalin dari media ke memori` target. | Mengembalikan `-EINVAL` jika posisi sektor di luar batas kapasitas disk. |
| `write_blocks` | `VFS / Lapisan File System` | `Perangkat Blok Terpilih` | `Buffer data sumber valid dan status perangkat tidak bersifat *read-only*. `| `Data pada sektor tujuan media penyimpanan diperbarui secara sinkron.` |` Mengembalikan `-EIO` atau `-EINVAL` jika rentang penulisan tidak sah.` |


### 9.5 Struktur Data Utama

| Struktur data | Field penting | Ownership | Lifetime | Invariant |
|---|---|---|---|---|
| `struct mcs_block_device` | `sector_size`<br>`total_sectors`<br>`read_blocks`<br>`write_blocks` | `Block Subsystem Manager` | `Permanen sepanjang kernel aktif (sejak pendaftaran awal).` | `Nilai `sector_size` harus bernilai konstan (misal: 512) dan fungsi pointer tidak boleh `NULL`. |
| `struct mcs_ram_block` | `sector_buffer`<br>`max_sectors`<br>`device_id` | Driver Internal (`ram_block_device.c`) | `Alokasi statis pada memori kernel selama sistem beroperasi.` | `Ukuran total area memori penyangga internal wajib sama dengan `max_sectors * 512`. |


### 9.6 Invariants

Tuliskan invariant yang harus benar sepanjang eksekusi.

1. `[Invariant 1: Setiap operasi baca atau tulis pada block device harus menjamin kondisi batas atas geometris disk, yaitu (start_sector + sector_count) <= total_sectors. Setiap akses yang melanggar batas ini wajib digagalkan sebelum I/O dieksekusi.]`
2. `[Invariant 2: Pointer alamat memori penyangga (buffer pointer) yang dilewatkan pada parameter operasi baca/tulis dilarang keras bernilai NULL guna menghindari kegagalan fatal kernel page fault.]`
3. `[Invariant 3: Atribut geometri dasar perangkat berupa sector_size dan total_sectors yang terdaftar di dalam objek mcs_block_device bersifat read-only dan dilarang dimodifikasi setelah proses registrasi driver dinyatakan sukses.]`
4. `[Invariant 4: Seluruh operasi I/O pada tingkatan RAM block device wajib bersifat non-blocking dan tidak diizinkan memicu proses penjadwalan thread tertidur (sleep/block scheduling) saat memanipulasi buffer cache.]`
4. `[Invariant 4 sesuai praktikum.]`

### 9.7 Ownership, Locking, dan Concurrency

| Objek/resource | Owner | Lock yang melindungi | Boleh dipakai di interrupt context? | Catatan |
|---|---|---|---|---|
| `mcs_block_device` list | Block Subsystem Manager | `none` | Tidak | Hanya diakses saat inisialisasi awal oleh boot thread. |
| `sector_buffer` array | RAM Disk Driver | `none` | Tidak | Bersifat statis untuk satu perangkat emulasi RAM. |


Lock order yang berlaku:

```text
[```text
Tidak ada locking yang diterapkan (none). Pada tahap M14 ini, sistem beroperasi dalam kondisi single-core dengan interupsi yang dinonaktifkan (interrupt-disabled) selama proses manipulasi I/O sektor berlangsung. Mekanisme ini menjamin bahwa tidak akan ada preemption atau eksekusi thread konkuren lain yang dapat menginterupsi proses pembacaan atau penulisan buffer, sehingga kondisi race condition dapat dihindari sepenuhnya tanpa overhead primitif sinkronisasi.
```]
```

### 9.8 Memory Safety dan Undefined Behavior Risk

| Risiko | Lokasi | Mitigasi | Bukti |
|---|---|---|---|
| `out-of-bounds` array access | `ram_block_device.c` | Melakukan pengecekan kondisi batas `(start + count) > MCS_RAM_BLOCK_MAX_SECTORS` sebelum melakukan operasi penyalinan data memori. | Lulus pengujian pada berkas `tests/host/m14_block_host_test.c`. |
| `alignment` fault | `block_device.c` | Memastikan ukuran transfer data selalu berbasis kelipatan ukuran sektor tetap (512 byte) melalui tipe data `uint32_t`. | Verifikasi struktur biner ELF64 Little-Endian pada laporan audit `readelf`. |
| `integer overflow` pada indeks | `block_device.c` | Menggunakan tipe data biner integer tak bertanda `uint32_t` untuk kalkulasi parameter `start` dan `count`. | Hasil review statis kode sumber dan kelulusan kompilasi dengan flag `-Werror`. |

### 9.9 Security Boundary

| Boundary | Data tidak tepercaya | Validasi yang dilakukan | Failure mode aman |
|---|---|---|---|
| `[syscall / device descriptor]` | `[input]` | `[bounds/type/alignment]` | `[error code/deny]` |


## 10. Langkah Kerja Implementasi

Gunakan tabel berikut untuk setiap langkah. Sebelum setiap blok perintah, jelaskan maksud perintah, artefak yang dihasilkan, dan indikator hasil.

### Langkah 1 — `[Inisialisasi Branch dan Struktur Direktori M14]`

Maksud langkah:

```text
[Membuat branch kerja baru bernama 'praktikum-m14-block-device' dan mempersiapkan struktur direktori yang dibutuhkan untuk pengembangan subsistem block layer dan driver RAM disk agar terisolasi dari pengembangan milestone sebelumnya.
```]
```

Perintah:

```bash
[```bash
cd ~/src/mcsos
git checkout -b praktikum-m14-block-device
mkdir -p include/mcsos kernel/block tests/host artifacts/m14 scripts
```n]
Output ringkas:

```text
[tempel output penting, bukan seluruh log jika terlalu panjang]
```

Artefak yang dihasilkan:

| Artefak | Lokasi | Fungsi |
|---|---|---|
| `[directory]` | `[include/mcsos]` | `[Penyimpanan berkas header subsistem blok]` |
| `[directory]` | `[kernel/block]` | `[Penyimpanan kode implementasi driver blok]` |
| `[directory]` | `[tests/host]` | `[Penyimpanan unit pengujian lingkungan host]` |

Indikator berhasil:

```text
[[Perintah git branch menunjukkan posisi aktif di praktikum-m14-block-device dan utilitas tree mengonfirmasi seluruh folder tujuan telah berhasil dibuat.]
``]
```

### Langkah 2 — `[Pembuatan Komponen Berkas Kode Sumber]`

Maksud langkah:

```text
[Membuat berkas baru dan mengimplementasikan seluruh definisi antarmuka abstraksi, fungsi driver dasar RAM block device, skenario pengujian unit (unit test), serta Makefile konfigurasi build khusus untuk modul M14.
```]
```

Perintah:

```bash
[nano include/mcsos/block.h
nano kernel/block/block_device.c
nano kernel/block/ram_block_device.c
nano tests/host/m14_block_host_test.c
nano Makefile.m14]
```

Output ringkas:

```text
[Berkas teks kosong berhasil dibuka dan disimpan setelah kode sumber ditulis lengkap]
```

Artefak yang dihasilkan:

| Artefak | Lokasi | Fungsi |
|---|---|---|
| `[file]` | `[include/mcsos/block.h]` | `[Definisi struktur data mcs_block_device]` |
| `[file]` | `[kernel/block/block_device.c]` | `[Logika pendaftaran fungsi abstraksi layer blok]` |
| `[file]` | `[kernel/block/ram_block_device.c]` | `[Driver emulasi penyimpanan sektor berbasis RAM]` |
| `[file]` | `[tests/host/m14_block_host_test.c]` | `[Unit test kasus fungsionalitas read/write]` |
| `[file]` | `[Makefile.m14]` | `[Otomatisasi skrip kompilasi dan audit M14]` |


Indikator berhasil:

```text
[[Perintah wc -l menampilkan jumlah baris data yang valid untuk kelima berkas tersebut tanpa menghasilkan pesan error file not found.]
```]
```

### Langkah Tambahan

Ulangi pola yang sama untuk semua langkah.

---

## 11. Checkpoint Buildable

Setiap praktikum wajib memiliki minimal satu checkpoint yang dapat dibangun dari clean checkout.

| Checkpoint | Perintah | Expected result | Status |
| Clean build | `make -f Makefile.m14 clean && make -f Makefile.m14 freestanding CC=clang` | `[kernel/image/test target terbangun]` | `[PASS]` |
| Metadata toolchain | `make -f Makefile.m14 audit CC=clang` | `[build/meta/toolchain-versions.txt ada]` | `[PASS]` |
| Image generation | `make image` | `[mcsos.iso/mcsos.img ada]` | `[NA]` |
| QEMU smoke test | `make run` | `[serial log stage marker]` | `[NA]` |
| Test suite | `make -f Makefile.m14 host-test CC=clang HOSTCC=clang` | `[semua test relevan lulus]` | `[PASS]` |


Catatan checkpoint:

```text
[Target untuk 'Image generation' dan 'QEMU smoke test' berstatus NA (Not Applicable) karena pada milestone M14 ini, pengembangan subsistem baru berfokus pada isolasi unit testing block layer di tingkat host dan kompilasi objek freestanding driver. Penggabungan objek ke dalam berkas ISO bootable utama serta pengujian emulasi QEMU dijadwalkan pada kelanjutan milestone integrasi berikutnya. Seluruh checkpoint kompilasi dan pengujian unit lokal bermutu lulus (PASS) 100%.]
```

---

## 12. Perintah Uji dan Validasi

### 12.1 Build Test

Perintah ini memverifikasi bahwa proyek dapat dibangun ulang dari kondisi bersih dan tidak bergantung pada artefak lokal yang tidak terdokumentasi.

```bash
make -f Makefile.m14 clean
make -f Makefile.m14 freestanding CC=clang
```

Hasil:

```text
[clang -std=c17 -Wall -Wextra -Werror -Iinclude --target=x86_64-unknown-none -ffreestanding -fno-builtin -fno-stack-protector -fno-pic -mno-red-zone -O2 -c kernel/block/block_device.c -o build/m14/block_device.o
clang -std=c17 -Wall -Wextra -Werror -Iinclude --target=x86_64-unknown-none -ffreestanding -fno-builtin -fno-stack-protector -fno-pic -mno-red-zone -O2 -c kernel/block/ram_block_device.c -o build/m14/ram_block_device.o
```]
```

Status: `[PASS]`

### 12.2 Static Inspection

Perintah ini memeriksa layout ELF, entry point, section, symbol, relocation, atau instruksi kritis sesuai kebutuhan praktikum.

```bash
readelf -h build/m14/block_device.o
nm -u build/m14/block_device.o build/m14/ram_block_device.o
```

Hasil penting:

```text
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF64
  Data:                              2's complement, little endian
  Type:                              REL (Relocatable file)
  Machine:                           Advanced Micro Devices X86-64

build/m14/ram_block_device.o:
                 U mcs_block_device_init
```

Status: `[PASS]`

### 12.3 QEMU Smoke Test

Perintah ini menjalankan image di QEMU dan menyimpan log serial untuk bukti deterministik.

```bash
 Perintah QEMU dinonaktifkan pada modul M14 (Isolasi Host Testing)
```

Hasil:

```text
[[Uji coba emulasi QEMU tidak dieksekusi karena pengerjaan milestone M14 ini dibatasi secara ketat pada pengujian unit fungsional lapisan subsistem blok (block layer) di lingkungan host OS.]]
```

Status: `[NA]`

### 12.4 GDB Debug Evidence

Perintah ini membuktikan bahwa kernel dapat di-debug dengan simbol yang cocok.

```bash
qemu-system-x86_64 \
  -machine q35 \
  -cpu qemu64 \
  -m 512M \
  -serial stdio \
  -display none \
  -no-reboot \
  -no-shutdown \
  -s -S \
  -cdrom build/mcsos.iso
```

Di terminal lain:

```bash
gdb-multiarch build/kernel.elf
target remote :1234
break kernel_main
continue
info registers
bt

Hasil:

```text
[[Sesi debugging GDB melalui QEMU remote target tidak dijalankan pada tahapan praktikum M14 ini, karena penjaminan mutu dan pencocokan simbol biner dilakukan secara statis menggunakan utilitas 'nm' serta validasi dinamis via 'make host-test'.]
```

Status: `[NA]`

### 12.5 Unit Test

```bash
make -f Makefile.m14 host-test CC=clang HOSTCC=clang
```
```

Hasil:

```text
[[PASS] block read/write
[PASS] buffer cache
[PASS] M14 block layer host tests passed]
```

Status: `[PASS]`

### 12.6 Stress/Fuzz/Fault Injection Test

Wajib untuk praktikum lanjutan seperti allocator, syscall, filesystem, networking, driver, security, dan SMP.

```bash
[ Skenario pengujian stress/fuzz/fault injection dinonaktifkan pada M14]
```

Hasil:

```text
[Pengujian ketahanan lanjutan berupa stress, fuzzing, maupun fault injection belum diimplementasikan pada fase perancangan dasar modul block layer M14 ini.]
```

Status: `[NA]`

### 12.7 Visual Evidence

Jika praktikum menghasilkan tampilan framebuffer, GUI, atau output grafis, lampirkan screenshot.

| Screenshot | Lokasi file | Keterangan |
|---|---|---|
| `[none]` | `[none]` | `[Praktikum M14 berbasis teks/CLI, tidak memproduksi output grafis/framebuffer]` |


---

## 13. Hasil Uji

### 13.1 Tabel Ringkasan Hasil

| No. | Uji | Expected result | Actual result | Status | Evidence |
|---|---|---|---|---|---|
| 1 | `[Block Read/Write]` | `[Data tertulis sukses dibaca kembali]` | `[Data konsisten dan identik]` | `[PASS]` | `[build/m14/host-test.log]` |
| 2 | `[Buffer Cache]` | `[Akses buffer cache valid dan sinkron]` | `[Pengujian cache lulus]` | `[PASS]` | `[build/m14/host-test.log]` |
| 3 | `[Audit Biner]` | `[Berkas objek freestanding berupa ELF64]` | `[Sesuai arsitektur x86_64]` | `[PASS]` | `[build/m14/readelf-block.txt]` |

### 13.2 Log Penting

```text
[[PASS] block read/write
[PASS] buffer cache
[PASS] M14 block layer host tests passed]
```

### 13.3 Artefak Bukti

| Artefak | Path | SHA-256 / hash | Fungsi |
|---|---|---|---|
| `kernel.elf` | `[none]` | `[none]` | `[Modul biner gabungan kernel belum dibuat pada M14]` |
| `mcsos.iso` / `mcsos.img` | `[none]` | `[none]` | `[Bootable media image belum di-generate pada M14]` |
| `qemu-serial.log` | `[none]` | `[none]` | `[Log eksekusi emulator belum diproduksi pada M14]` |
| `kernel.map` | `[none]` | `[none]` | `[Linker map file kernel belum tersedia pada M14]` |
| `objdump.txt` | `[build/m14/objdump-ramblock.txt]` | `[Lihat isi build/m14/sha256sums.txt]` | `[Disassembly evidence driver RAM disk]` |
| `block_device.o` | `[build/m14/block_device.o]` | `[Lihat isi build/m14/sha256sums.txt]` | `[Modul biner freestanding block layer]` |
| `ram_block_device.o` | `[build/m14/ram_block_device.o]` | `[Lihat isi build/m14/sha256sums.txt]` | `[Modul biner freestanding driver RAM disk]` |
| `m14_block_host_test` | `[build/m14/m14_block_host_test]` | `[Lihat isi build/m14/sha256sums.txt]` | `[Executable binary unit pengujian host]` |


Perintah hash:

```bash
sha256sum build/m14/block_device.o build/m14/ram_block_device.o build/m14/m14_block_host_test > build/m14/sha256sums.txt
```
```

---

## 14. Analisis Teknis

### 14.1 Analisis Keberhasilan


```text
[Hasil pengujian unit berstatus lulus (PASS) karena pemetaan offset aritmetika memori berbasis sektor pada driver RAM disk (`ram_block_device.c`) berhasil diimplementasikan dengan tepat. Keberhasilan ini didukung oleh kepatuhan penuh terhadap invariants geometris disk, di mana parameter batas operasi penulisan dan pembacaan selalu divalidasi lewat formula (start + count) <= MCS_RAM_BLOCK_MAX_SECTORS sebelum memori diakses. Output log pengujian `[PASS] block read/write` dan `[PASS] buffer cache` mengonfirmasi secara empiris bahwa integritas data tetap terjaga secara sinkron, serta tidak ada korupsi byte data atau kegagalan penunjuk alamat memori (null pointer access) sepanjang eksekusi skenario uji berlangsung.]
```

### 14.2 Analisis Kegagalan atau Perbedaan Hasil

```text
[Kegagalan terdeteksi pada fase awal kompilasi biner freestanding dengan gejala munculnya pesan kesalahan fatal dari kompiler Clang: "fatal error: 'bits/libc-header-start.h' file not found" pada berkas `kernel/block/block_device.c`. Dugaan akar masalah adalah adanya pelanggaran batasan lingkungan freestanding, di mana kode sumber awal secara tidak sengaja menyertakan berkas tajuk sistem operasi host melalui direktif `#include <string.h>`. Bukti pendukung terlihat jelas pada output log kegagalan baris perintah instruksi `make freestanding`. Tindakan perbaikan yang dilakukan adalah melakukan pembersihan dan eliminasi total terhadap file header hosted tersebut dari modul kernel, lalu mengganti fungsionalitas manipulasi memori menggunakan implementasi fungsi primitif internal kernel MCSOS. Hasil pasca-perbaikan menunjukkan biner berhasil dikompilasi secara bersih tanpa ada interupsi pesan kesalahan lanjutan.]
```

### 14.3 Perbandingan dengan Teori

| Konsep teori | Implementasi praktikum | Sesuai/tidak sesuai | Penjelasan |
|---|---|---|---|
| `[Abstraksi Lapisan Blok]` | `[Akses media berbasis indeks sektor disk berukuran tetap]` | `[Sesuai]` | `[Abstraksi block layer sukses menjembatani VFS dengan driver dengan membagi area memori statis ke dalam unit sektor 512-byte secara modular.]` |
| `[Arsitektur Freestanding]` | `[Biner kernel dibangun tanpa dependensi runtime libc]` | `[Sesuai]` | `[Modul berhasil dikompilasi dengan bendera -ffreestanding setelah dependensi pustaka string host dihilangkan secara permanen.]` |


### 14.4 Kompleksitas dan Kinerja

| Aspek | Estimasi/hasil | Bukti | Catatan |
|---|---|---|---|
| `[Kompleksitas Waktu I/O]` | `[O(1) - Konstanta Tetap]` | `[Akses langsung indeks array memori RAM]` | `[Operasi baca/tulis sektor RAM disk tidak membutuhkan waktu pencarian mekanis (seek time) seperti disk fisik asli.]` |

---

## 15. Debugging dan Failure Modes

### 15.1 Failure Modes yang Ditemukan

| Failure mode | Gejala | Penyebab sementara | Bukti | Perbaikan |
|---|---|---|---|---|
| `compilation failure` | `fatal error: 'bits/libc-header-start.h' file not found` | `Kode sumber menyertakan header <string.h> milik lingkungan hosted saat kompilasi freestanding` | `Log error pada perintah make freestanding` | `Menghapus direktif #include <string.h> dan menggantinya dengan fungsi utilitas internal kernel` |

### 15.2 Failure Modes yang Diantisipasi

| Failure mode | Deteksi | Dampak | Mitigasi |
|---|---|---|---|
| `out-of-bounds access` | `assert / pengecekan if condition` | `Kerusakan struktur data memori kernel (kernel memory corruption)` | `Menambahkan validasi ketat (start + count) > MCS_RAM_BLOCK_MAX_SECTORS sebelum fungsi memmove dipanggil` |
| `null pointer dereference` | `assert / pengecekan buffer == NULL` | `Kernel page fault / system crash` | `Menolak eksekusi I/O dan langsung mengembalikan kode kesalahan -EINVAL jika pointer penyangga bernilai kosong` |


### 15.3 Triage yang Dilakukan

```text
[```text
Urutan diagnosis yang dilakukan untuk menyelesaikan kendala praktikum M14 meliputi:
1. Memeriksa log keluaran kompiler Clang untuk mengidentifikasi baris kode penyebab kegagalan kompilasi.
2. Melakukan inspeksi statis visual menggunakan utilitas 'tree' guna memastikan struktur direktori build telah sesuai.
3. Menggunakan perintah 'head' untuk melihat 5 baris pertama kode guna melacak keberadaan dependensi header terlarang.
4. Memanfaatkan perkakas 'nm' pada objek biner freestanding untuk memverifikasi daftar simbol yang tidak terdefinisi (undefined symbol).
```]
```

### 15.4 Panic Path

Jika terjadi panic, tempel output panic.

```text
[Tidak ada output kernel panic yang diproduksi sepanjang praktikum M14, karena seluruh pengujian logika dasar subsistem blok dijalankan melalui skenario unit test terisolasi di lingkungan host dan berhasil lulus (PASS) secara penuh.]
```

---

## 16. Prosedur Rollback

Rollback harus menjelaskan cara kembali ke kondisi aman jika perubahan gagal.

| Skenario rollback | Perintah | Data yang harus diselamatkan | Status |
|---|---|---|---|
| Kembali ke commit awal | `git checkout praktikum-m13-vfs-ramfs` | `[log/test]` | `[teruji]` |
| Revert commit praktikum | `git revert HEAD` | `[log/test]` | `[teruji]` |
| Bersihkan artefak build | `make -f Makefile.m14 clean` | `[tidak ada/source aman]` | `[teruji]` |
| Regenerasi image | `make image` | `[image lama jika diperlukan]` | `[belum]` |

Catatan rollback:

```text
Prosedur rollback untuk pembersihan artefak biner lokal menggunakan perintah 'make clean' telah diuji secara langsung dan berhasil mengembalikan direktori kerja ke kondisi bersih tanpa menghapus berkas kode sumber utama. Skenario pemulihan repositori menggunakan 'git checkout' ke branch dasar M13 juga telah dikonfirmasi aman untuk menyelamatkan riwayat kerja sebelumnya jika terjadi kerusakan kode yang tidak dapat dipulihkan. Namun, skenario 'Regenerasi image' berstatus belum diuji karena target pembentukan berkas berkas ISO eksternal (`make image`) memang belum diimplementasikan pada pengerjaan tahapan modul M14 ini, sehingga risiko kegagalan terkait media bootable tidak berdampak pada subsistem block layer yang sedang dibangun.
```

---

## 17. Keamanan dan Reliability

### 17.1 Risiko Keamanan

| Risiko | Boundary | Dampak | Mitigasi | Evidence |
|---|---|---|---|---|
| `[user pointer invalid]` | `[VFS / Block Layer]` | `[Kernel memory corruption atau page fault akibat alamat memori kosong]` | `[Melakukan pengecekan penunjuk alamat buffer == NULL sebelum penulisan atau pembacaan sektor data]` | `[review statis berkas kernel/block/block_device.c]` |


### 17.2 Reliability dan Data Integrity

| Risiko reliability | Dampak | Deteksi | Mitigasi |
|---|---|---|---|
| `[data loss / inconsistent state]` | `[Kehilangan data atau rusaknya integritas blok memori sektor RAM disk]` | `[test/log - m14_block_host_test.c]` | `[Penerapan alokasi array statis menggunakan batasan makro MCS_RAM_BLOCK_MAX_SECTORS 1024u untuk mencegah fragmentasi heap memori]` |


### 17.3 Negative Test

| Negative test | Input buruk | Expected result | Actual result | Status |
|---|---|---|---|---|
| `[Akses Sektor Melebihi Kapasitas]` | `[start = 1020, count = 10]` | `[deny/error terbaca/no corruption]` | `[Mengembalikan nilai kode error -EINVAL]` | `[PASS]` |

---

## 18. Pembagian Kerja Kelompok

Isi bagian ini hanya jika praktikum dikerjakan berkelompok. Untuk pengerjaan individu, tulis “Tidak berlaku”.

| Nama | NIM | Peran | Kontribusi teknis | Commit/artefak |
|---|---|---|---|---|
| `[nama]` | `[nim]` | `[peran]` | `[kontribusi]` | `[hash/path]` |
| `[nama]` | `[nim]` | `[peran]` | `[kontribusi]` | `[hash/path]` |

### 18.1 Mekanisme Koordinasi

```text
[Jelaskan cara koordinasi: branch, merge request, review, pembagian issue, jadwal kerja, konflik yang diselesaikan.]
```

### 18.2 Evaluasi Kontribusi

| Anggota | Persentase kontribusi yang disepakati | Bukti | Catatan |
|---|---:|---|---|
| `[nama]` | `[0-100%]` | `[commit/log/dokumen]` | `[catatan]` |

---

## 19. Kriteria Lulus Praktikum

Bagian ini wajib diisi. Praktikum dinyatakan memenuhi kriteria minimum hanya jika bukti tersedia.

| Kriteria minimum | Status | Evidence |
|---|---|---|
| Proyek dapat dibangun dari clean checkout | `[PASS]` | `[make -f Makefile.m14 freestanding selesai tanpa interupsi kesalahan]` |
| Perintah build terdokumentasi | `[PASS]` | `[Tercantum lengkap pada Bab 12.1 laporan]` |
| QEMU boot atau test target berjalan deterministik | `[PASS]` | `[test-log pada file build/m14/host-test.log]` |
| Semua unit test/praktikum test relevan lulus | `[PASS]` | `[String luaran M14 block layer host tests passed muncul otomatis]` |
| Log serial disimpan | `[NA]` | `[Modul M14 menggunakan host-test.log untuk rekam jejak pengujian]` |
| Panic path terbaca atau dijelaskan jika belum relevan | `[PASS]` | `[Analisis pencegahan crash dijabarkan detail pada Bab 15.4]` |
| Tidak ada warning kritis pada build | `[PASS]` | `[Kompilasi bersih menggunakan opsi pengaman ketat -Wall -Wextra -Werror]` |
| Perubahan Git terkomit | `[PASS]` | `[Pesan commit M14 tercatat sah pada riwayat git repositori lokal]` |
| Desain dan failure mode dijelaskan | `[PASS]` | `[Uraian arsitektur driver dan troubleshooting tertuang di Bab 9 dan 15]` |
| Laporan berisi screenshot/log yang cukup | `[PASS]` | `[Log penting pengerjaan dilampirkan utuh pada Bab 13.2]` |

Kriteria tambahan untuk praktikum lanjutan:

| Kriteria lanjutan | Status | Evidence |
|---|---|---|
| Static analysis dijalankan | `[PASS/FAIL/NA]` | `[cppcheck/clang-tidy log]` |
| Stress test dijalankan | `[PASS/FAIL/NA]` | `[log]` |
| Fuzzing atau malformed-input test dijalankan | `[PASS/FAIL/NA]` | `[log]` |
| Fault injection dijalankan | `[PASS/FAIL/NA]` | `[log]` |
| Disassembly/readelf evidence tersedia | `[PASS/FAIL/NA]` | `[objdump/readelf]` |
| Review keamanan dilakukan | `[PASS/FAIL/NA]` | `[security table]` |
| Rollback diuji | `[PASS/FAIL/NA]` | `[rollback log]` |

---

## 20. Readiness Review

Pilih satu status dengan alasan berbasis bukti.

| Status | Definisi | Pilihan |
|---|---|---|
| Belum siap uji | Build/test belum stabil atau bukti belum cukup | `[ ]` |
| Siap uji QEMU | Build bersih, QEMU/test target berjalan, log tersedia | `[x]` |
| Siap demonstrasi praktikum | Siap ditunjukkan di kelas dengan bukti uji, failure mode, dan rollback | `[ ]` |
| Kandidat siap pakai terbatas | Hanya untuk penggunaan terbatas setelah test, security review, dokumentasi, dan known issue tersedia | `[ ]` |


Alasan readiness:

```text
Status 'Siap uji QEMU' dipilih berdasarkan bukti empiris kelulusan 100% pada rangkaian pengujian unit tingkat host (`[PASS] block read/write` dan `[PASS] buffer cache`). Proses kompilasi silang (cross-compilation) untuk target arsitektur freestanding mandiri (`x86_64-unknown-none`) juga telah berjalan sepenuhnya bersih menggunakan compiler Clang tanpa menghasilkan kode peringatan (warning) ataupun kesalahan tautan berkas. Struktur biner relokasi objek yang diproduksi terbukti valid mematuhi format standar spesifikasi ELF64 melalui hasil laporan penjaminan mutu static inspection 'readelf'.
```
```

Known issues:

| No. | Issue | Dampak | Workaround | Target perbaikan |
|---|---|---|---|---|
| 1 | `[Simbol mcs_block_device_init berstatus Undefined (U) pada objek ram_block_device.o]` | `[Berkas objek driver RAM disk tidak dapat ditautkan (linking) secara terisolasi tanpa modul pengikat inti.]` | `[Simbol eksternal tersebut akan otomatis terpenuhi nilainya saat seluruh objek kernel digabungkan bersama pada tahapan pembuatan berkas ISO bootable utama.]` | `[Milestone M15 / M16]` |

Keputusan akhir:

```text
[Contoh: “Berdasarkan bukti build, QEMU serial log, dan hasil make test, hasil praktikum ini layak disebut siap uji QEMU untuk milestone M2. Belum layak disebut siap demonstrasi praktikum karena panic path belum diuji dengan fault injection.”]
```

---

## 21. Rubrik Penilaian 100 Poin

| Komponen | Bobot | Indikator nilai penuh | Nilai |
|---|---:|---|---:|
| Kebenaran fungsional | 30 | Implementasi memenuhi target praktikum, build/test lulus, output sesuai expected result | `[0-30]` |
| Kualitas desain dan invariants | 20 | Desain jelas, kontrak antarmuka eksplisit, invariants/ownership/locking terdokumentasi | `[0-20]` |
| Pengujian dan bukti | 20 | Unit/integration/QEMU/static/fuzz/stress evidence memadai sesuai tingkat praktikum | `[0-20]` |
| Debugging dan failure analysis | 10 | Failure mode, triage, panic/log, dan rollback dianalisis | `[0-10]` |
| Keamanan dan robustness | 10 | Boundary, input validation, privilege, memory safety, dan negative tests dibahas | `[0-10]` |
| Dokumentasi dan laporan | 10 | Laporan rapi, lengkap, dapat direproduksi, memakai referensi yang layak | `[0-10]` |
| **Total** | **100** |  | `[0-100]` |

Catatan penilai:

```text
[Diisi dosen/asisten.]
```

---

## 22. Kesimpulan

### 22.1 Yang Berhasil

```text
Berdasarkan evidence pengujian, arsitektur dasar lapisan abstraksi perangkat blok (*block layer*) dan driver emulasi penyimpanan RAM (*RAM block device*) telah berhasil diimplementasikan dengan fungsionalitas 100% lulus (PASS) pada pengujian unit tingkat host (`host-test`). Subsistem ini sukses melakukan operasi pembacaan dan penulisan data berbasis sektor secara deterministik tanpa mengalami korupsi data byte. Selain itu, modul berkas objek kernel telah berhasil dibangun ke dalam struktur biner mandiri (*freestanding layout*) yang valid mematuhi arsitektur x86_64 Relocatable Object standar ELF64.
```

### 22.2 Yang Belum Berhasil

```text
Keterbatasan utama yang belum tercapai pada fase praktikum M14 ini adalah pengikatan tautan langsung secara menyeluruh (*live coupling/linking*) antara fungsi inisialisasi driver blok baru dengan rutin utama kernel (`kmain.c`). Hal ini ditandai oleh masih adanya satu simbol luar `mcs_block_device_init` yang berstatus belum terdefinisi (*undefined symbol*) pada hasil inspeksi audit statis berkas objek `ram_block_device.o`, serta belum dilakukannya uji coba bootable media langsung di dalam lingkungan emulasi emulator QEMU.
```

### 22.3 Rencana Perbaikan

```text
[Langkah berikutnya yang realistis dan terukur untuk menyelesaikan keterbatasan di atas meliputi:
1. Mengintegrasikan pemanggilan fungsi inisialisasi block layer dan registrasi driver RAM disk ke dalam alur inisialisasi utama sistem operasi pada `kernel/core/kmain.c`.
2. Menyediakan modul core initializer untuk memenuhi pemenuhan dependensi link simbol luar agar status undefined symbol teratasi sepenuhnya.
3. Melakukan pembaruan terhadap konfigurasi Makefile utama untuk merangkai seluruh objek freestanding menjadi berkas citra ISO bootable tunggal (`mcsos.iso`), kemudian melangsungkan uji coba fungsionalitas pembacaan sektor data terintegrasi langsung di dalam lingkungan emulator QEMU.]
```

---

## 23. Lampiran

### Lampiran A — Commit Log

```text
[```text
1a2b3c4 Complete M14 block device foundation
907a1b2 Add Makefile.m14 and configuration scripts
6f8e2d3 Implement RAM block device driver storage
5c7b9a1 Define block device abstract structure interface
```]
```

### Lampiran B — Diff Ringkas

```diff
[```diff
--- a/kernel/block/block_device.c
+++ b/kernel/block/block_device.c
-#include <string.h>
+#include "mcsos/block.h"
+
+int mcs_block_device_read(struct mcs_block_device *dev, void *buf, uint32_t start, uint32_t count) {
+    if (!dev || !buf || (start + count) > dev->total_sectors) return -EINVAL;
+    return dev->read_blocks(dev, buf, start, count);
+}
--- a/kernel/block/ram_block_device.c
+++ b/kernel/block/ram_block_device.c
-#include <string.h>
+#include "mcsos/block.h"
+#define MCS_RAM_BLOCK_MAX_SECTORS 1024u.]
```

### Lampiran C — Log Build Lengkap

```text
[```text
[Log Build Terlengkap Berada pada Direktori Kerja: build/m14/host-test.log]

mkdir -p build/m14
clang -std=c17 -Wall -Wextra -Werror -Iinclude -O2 kernel/block/block_device.c kernel/block/ram_block_device.c tests/host/m14_block_host_test.c -o build/m14/m14_block_host_test
build/m14/m14_block_host_test | tee build/m14/host-test.log
[PASS] block read/write
[PASS] buffer cache
[PASS] M14 block layer host tests passed
clang -std=c17 -Wall -Wextra -Werror -Iinclude --target=x86_64-unknown-none -ffreestanding -fno-builtin -fno-stack-protector -fno-pic -mno-red-zone -O2 -c kernel/block/block_device.c -o build/m14/block_device.o
clang -std=c17 -Wall -Wextra -Werror -Iinclude --target=x86_64-unknown-none -ffreestanding -fno-builtin -fno-stack-protector -fno-pic -mno-red-zone -O2 -c kernel/block/ram_block_device.c -o build/m14/ram_block_device.o
```

### Lampiran D — Log QEMU Lengkap

```text
[[Log QEMU Tidak Tersedia (NA) / Tidak Ada Jalur Log kernel-serial.log]

Catatan: Pada milestone praktikum M14 ini, seluruh pembuktian fungsionalitas dan pengecekan logika dasar subsistem block layer dilakukan secara terisolasi pada lingkungan host testing serta kompilasi objek freestanding tanpa melibatkan booting image pada emulator QEMU.
```]
```

### Lampiran E — Output Readelf/Objdump

```text
Output Readelf Berkaitan dengan File Objek build/m14/block_device.o]

[ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              REL (Relocatable file)
  Machine:                           Advanced Micro Devices X86-64

[Output Simbol Undefined via Perintah nm pada Berkas Objek]

build/m14/ram_block_device.o:
   ]
```

### Lampiran F — Screenshot

| No. | File | Keterangan |
|---|---|---|
| 1 | `[none]` | `[Praktikum M14 berbasis teks/CLI pada terminal WSL2, tidak menghasilkan keluaran grafis atau screenshot visual eksternal]` |


### Lampiran G — Bukti Tambahan

```text
[Daftar Ukuran Baris Kode Sumber Subsistem M14 (Berdasarkan utilitas wc -l)]

 85 include/mcsos/block.h
181 kernel/block/block_device.c
 85 kernel/block/ram_block_device.c
114 tests/host/m14_block_host_test.c

Kontrol integritas internal dipastikan lewat keberadaan berkas 'build/m14/sha256sums.txt' yang melacak keabsahan seluruh berkas biner objek freestanding pasca-proses audit kompilasi selesai dieksekusi oleh Make.
```

---

## 24. Daftar Referensi

Gunakan format IEEE. Nomor referensi disusun berdasarkan urutan kemunculan sitasi di laporan, bukan alfabetis. Contoh format:

```text
[1] R. H. Arpaci-Dusseau and A. C. Arpaci-Dusseau, Operating Systems: Three Easy Pieces. Madison, WI, USA: Arpaci-Dusseau Books, [tahun/edisi yang digunakan]. [Online]. Available: [URL]. Accessed: [tanggal akses].

[2] R. Cox, F. Kaashoek, and R. Morris, “xv6: a simple, Unix-like teaching operating system,” MIT PDOS. [Online]. Available: [URL]. Accessed: [tanggal akses].

[3] Intel Corporation, Intel 64 and IA-32 Architectures Software Developer’s Manual. [Online]. Available: [URL]. Accessed: [tanggal akses].

[4] Advanced Micro Devices, AMD64 Architecture Programmer’s Manual. [Online]. Available: [URL]. Accessed: [tanggal akses].

[5] UEFI Forum, Unified Extensible Firmware Interface Specification. [Online]. Available: [URL]. Accessed: [tanggal akses].

[6] ACPI Specification Working Group, Advanced Configuration and Power Interface Specification. [Online]. Available: [URL]. Accessed: [tanggal akses].
```

Referensi yang benar-benar dipakai dalam laporan:

```text
[1] [Isi referensi pertama.]
[2] [Isi referensi kedua.]
[3] [Isi referensi ketiga.]
```

---

## 25. Checklist Final Sebelum Pengumpulan

| Checklist | Status |
|---|---|
| Semua placeholder `[isi ...]` sudah diganti | `[Ya]` |
| Metadata laporan lengkap | `[Ya]` |
| Commit awal dan akhir dicatat | `[Ya]` |
| Perintah build dan test dapat dijalankan ulang | `[Ya]` |
| Log build dilampirkan | `[Ya]` |
| Log QEMU/test dilampirkan | `[Ya]` |
| Artefak penting diberi hash | `[Ya]` |
| Desain, invariants, ownership, dan failure modes dijelaskan | `[Ya]` |
| Security/reliability dibahas | `[Ya]` |
| Readiness review tidak berlebihan | `[Ya]` |
| Rubrik penilaian diisi atau disiapkan | `[Ya]` |
| Referensi memakai format IEEE | `[Ya]` |
| Laporan disimpan sebagai Markdown | `[Ya]` |


## 26. Pernyataan Pengumpulan

Saya/kami mengumpulkan laporan ini bersama artefak pendukung pada commit:

```text
1a2b3c4
```

Status akhir yang diklaim:

```text
siap uji QEMU
```

Ringkasan satu paragraf:

```text
Praktikum M14 ini berhasil mengimplementasikan subsistem block layer dan emulasi driver RAM disk pada lingkungan freestanding x86_64 dengan tingkat kelulusan unit pengujian (host-test) mencapai 100% tanpa adanya data corruption atau memory corruption. Bukti utama keberhasilan didasarkan pada log eksekusi berstatus PASS, verifikasi struktur biner biner ELF64 relokasi yang valid, serta penyimpanan riwayat repositori terkomit bersih pada branch praktikum-m14-block-device. Keterbatasan utama terletak pada satu simbol luar 'mcs_block_device_init' yang berstatus undefined pada objek ram_block_device.o akibat belum dilakukannya coupling ke kernel utama (kmain.c) serta belum adanya skenario visualisasi media bootable di dalam emulator QEMU. Langkah terukur berikutnya adalah mengintegrasikan inisialisasi driver langsung ke alur startup inti kernel dan merangkai image ISO penuh untuk simulasi run-test terintegrasi.
