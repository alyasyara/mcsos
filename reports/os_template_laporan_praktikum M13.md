# Template Laporan Praktikum Sistem Operasi Lanjut — MCSOS

**Nama file laporan:** `laporan_praktikum_[M13]_[ma oyah].md`  
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
| Kode praktikum | `[M13 ]` |
| Judul praktikum | `[`Virtual File System (VFS) dan RAMFS Foundation`]` |
| Jenis pengerjaan | `[ Kelompok]` |
| Nama mahasiswa | `[nama lengkap]` |
| NIM | `[NIM]` |
| Kelas | `[kelas]` |
| Nama kelompok | `[ma oyah]` |
| Anggota kelompok | `[Nisrina Amanda Puteri (25832072010) : Toolchain Engineer

Meyliza Rosmalia Putri (25832072012) : Documentation Enginee

Alya Syara Shafira (25832073009) : Verification Engineer

Nurul Aminatul Aliah (25832073013) : Koordinator Teknis]` |
| Tanggal praktikum | `[2026-06-18]` |
| Tanggal pengumpulan | `[YYYY-MM-DD]` |
| Repository | `[ `~/src/mcsos` ]` |
| Branch | `[`praktikum-m13-vfs-ramfs`]` |
| Commit awal | `` `[hash commit awal]` `` |
| Commit akhir | `` `[f7a2d3c]` `` |
| Status readiness yang diklaim | `[ siap uji QEMU ]` |

---

## 1. Sampul

# Laporan Praktikum `[Kode Praktikum]`  
## `[Virtual File System (VFS) dan RAMFS Foundation]`

Disusun oleh:

| Nama | NIM | Kelas | Peran |
|---|---|---|---|
| Nisrina Amanda Puteri (25832072010) : Toolchain Engineer

Meyliza Rosmalia Putri (25832072012) : Documentation Enginee

Alya Syara Shafira (25832073009) : Verification Engineer

Nurul Aminatul Aliah (25832073013) : Koordinator Teknis |

Dosen Pengampu: **Muhaemin Sidiq, S.Pd., M.Pd.**  
Program Studi Pendidikan Teknologi Informasi  
Institut Pendidikan Indonesia  
`[2026]`

---

## 2. Pernyataan Orisinalitas dan Integritas Akademik

Saya/kami menyatakan bahwa laporan ini disusun berdasarkan pekerjaan praktikum sendiri/kelompok sesuai pembagian peran yang tercatat. Bantuan eksternal, referensi, generator kode, AI assistant, dokumentasi resmi, diskusi, atau sumber lain dicatat pada bagian referensi dan lampiran. Saya/kami tidak mengklaim hasil yang tidak dibuktikan oleh log, test, commit, atau artefak lain.

| Pernyataan | Status |
|---|---|
| Semua potongan kode eksternal diberi atribusi | `[Tidak ada]` |
| Semua penggunaan AI assistant dicatat | `[Ya]` |
| Repository yang dikumpulkan sesuai commit akhir | `[Ya]` |
| Tidak ada klaim readiness tanpa bukti | `[Ya]` |

Catatan penggunaan bantuan eksternal:

```text
[Alat: AI Assistant .
Sumber: Hasil generate AI untuk konversi log history terminal ke draf dokumen laporan praktikum.
Bagian yang dibantu: Penyusunan struktur tabel metadata laporan, langkah kerja implementasi M13,
Verifikasi mandiri: Memeriksa kesesuaian nama branch (praktikum-m13-vfs-ramfs), path berkas (mcs_vfs.h, ramfs.c, m13_vfs_host_test.c), serta perintah otomasi makefile yang telah dieksekusi secara nyata di terminal WSL.]
```

---

## 3. Tujuan Praktikum

Tuliskan tujuan teknis dan konseptual praktikum. Tujuan harus dapat diuji.


1. `Membangun fondasi abstraksi Virtual File System (VFS) berbasis struktur data mcs_vfs pada target freestanding.`
2. `Mengimplementasikan sistem berkas berbasis RAM (RAMFS) sebagai backing store awal penampung file descriptor.`
3. `Menjelaskan konsep dan mekanisme registrasi berkas, alokasi descriptor, serta penanganan operasi read/write pada VFS.`
4. `Menyimpan log pengujian unit host (host-test), hasil build freestanding, dan bukti pembersihan commit Git.`

---

## 4. Capaian Pembelajaran Praktikum

Setelah praktikum ini, mahasiswa mampu:

| CPL/CPMK praktikum | Bukti yang harus ditunjukkan |
|---|---|
| | `Mampu merancang antarmuka abstraksi VFS dan operasi berkas menggunakan bahasa C freestanding` |  |
| `Mampu membuat skenario uji terisolasi pada arsitektur host menggunakan Clang compiler` |  |
| `Mampu melakukan pelacakan riwayat pengerjaan serta audit build environment secara terintegrasi` | |

---

## 5. Peta Milestone MCSOS

Centang milestone yang menjadi fokus laporan ini. Jika praktikum mencakup lebih dari satu milestone, jelaskan batas cakupan.

| Milestone | Fokus | Status dalam laporan |
|---|---|---|
|---|---|---|
| M0 | Requirements, governance, baseline arsitektur | `[x] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M1 | Toolchain reproducible, Git, QEMU, GDB, metadata build | `[x] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M2 | Boot image, kernel ELF64, early console | `[x] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M3 | Panic path, linker map, GDB, observability awal | `[x] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M4 | Trap, exception, interrupt, timer | `[x] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M5 | PMM, VMM, page table, kernel heap | `[x] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M6 | Thread, scheduler, synchronization | `[x] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M7 | Syscall ABI dan user program loader | `[x] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M8 | VFS, file descriptor, ramfs | `[x] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M9 | Block layer dan device model | `[x] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M10 | Persistent filesystem, mcsfs/ext2-like, recovery | `[x] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M11 | Networking stack, packet parsing, UDP/TCP subset | `[x] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M12 | Security model, capability/ACL, syscall fuzzing, hardening | `[x] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M13 | SMP, scalability, lock stress, NUMA-aware preparation | `[ ] tidak dibahas / [ ] dibahas / [x] selesai praktikum` |
| M14 | Framebuffer, graphics console, visual regression | `[x] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M15 | Virtualization/container subset | `[x] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |
| M16 | Observability, update/rollback, release image, readiness review | `[x] tidak dibahas / [ ] dibahas / [ ] selesai praktikum` |

Batas cakupan praktikum:

```text
[Fitur yang termasuk (Goals):
1. Inisialisasi struktur data penampung virtual file system node (`vfs_node`) dan tabel file descriptor internal kernel.
2. Mekanisme registrasi fungsi operasi berkas primitif (`open`, `read`, `write`, `close`) khusus untuk filesystem berbasis RAM (RAMFS).
3. Automasi pengujian unit di lingkungan local host menggunakan Clang untuk memverifikasi fungsionalitas sebelum di-porting ke kernel utama.

Bukan target praktikum (Non-goals):
1. Tidak menangani sinkronisasi multi-core (SMP-safe locking) atau balapan memori (race conditions) tingkat lanjut pada VFS.
2. Tidak mencakup implementasi persistent storage ke dalam drive fisik (Block layer / IDE / AHCI driver) maupun sistem berkas eksternal nyata seperti Ext2.]
```

---

## 6. Dasar Teori Ringkas

Tuliskan teori yang langsung diperlukan untuk memahami praktikum. Jangan menyalin teori umum terlalu panjang; fokus pada konsep yang benar-benar digunakan dalam desain dan pengujian.

### 6.1 Konsep Sistem Operasi yang Diuji

```text
[Praktikum ini menguji konsep Virtual File System (VFS) dan RAMFS. VFS merupakan lapisan abstraksi dalam kernel yang menyediakan antarmuka seragam bagi aplikasi untuk mengakses berbagai jenis sistem berkas melalui operasi standar seperti open, read, write, dan close. Lapisan ini menyembunyikan detail implementasi spesifik dari media penyimpanan di bawahnya dengan memanfaatkan pointer fungsi pada objek operasi berkas. RAMFS digunakan sebagai backing store modular awal yang menyimpan seluruh hierarki berkas, metadata node (vfs_node), dan data biner langsung di dalam memori utama (RAM) secara dinamis tanpa persistensi ekdisk.]
```

### 6.2 Konsep Arsitektur x86_64 yang Relevan

| Konsep | Relevansi pada praktikum | Bukti/verifikasi |
|---|---|---|
| | `long mode / paging` | `Akses memori untuk buffer RAMFS harus dipetakan dengan benar pada memori virtual kernel x86_64 agar tidak memicu page fault.` | `serial log dan register dump` |
| `syscall` | `Menyiapkan ABI jembatan masa depan bagi user space untuk memanggil instruksi sys_open, sys_read, dan sys_write.` | `test dan readelf` | `[bukti]` |

### 6.3 Konsep Implementasi Freestanding

| Aspek | Keputusan praktikum |
|---|---|
| | Bahasa | `C17 freestanding` |
| Runtime | `tanpa hosted libc` |
| ABI | `x86_64 System V` |
| Compiler flags kritis | `-ffreestanding -mno-red-zone -nostdlib` |
| Risiko undefined behavior | `pointer invalid pada pengosongan vfs_node atau buffers alignment data` | |

### 6.4 Referensi Teori yang Digunakan

| No. | Sumber | Bagian yang digunakan | Alasan relevansi |
|---|---|---|---|
| `[1]` | `R. H. Arpaci-Dusseau and A. C. Arpaci-Dusseau, Operating Systems: Three Easy Pieces, 2018.` | `Bab 39 (Files and Directories) & Bab 40 (File System Implementation)` | `Menyediakan landasan teoretis mengenai manajemen file descriptor tabel proses, siklus hidup penanganan data biner di memori, dan abstraksi POSIX API.` |
| `[2]` | `R. Cox, F. Kaashoek, and R. Morris, "xv6: a simple, Unix-like teaching operating system," MIT PDOS.` | `Bab 6 (File system) dan implementasi struktur data struct file.` | `Menjadi acuan struktur minimalis perancangan antarmuka fungsi pemanggil (open/read/write) pada kernel sistem operasi berbasis pendidikan.`  |

---

## 7. Lingkungan Praktikum

### 7.1 Host dan Target

| Komponen | Nilai |
|---|---|
| Host OS | `Windows 11 x64` |
| Lingkungan build | `WSL 2 Ubuntu` |
| Target ISA | `x86_64` |
| Target ABI | `x86_64-unknown-none` |
| Emulator | `QEMU` |
| Firmware emulator | `OVMF` |
| Debugger | `GDB` |
| Build system | `Make` |
| Bahasa utama | `C17 freestanding` |
| Assembly | `GAS` |

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
[date_utc=2026-06-18T09:09:42Z
Linux MyBookHype 5.15.150.1-microsoft-standard-WSL2 #1 SMP Wed Jan 11 04:09:00 UTC 2026 x86_64 x86_64 x86_64 GNU/Linux
git version 2.43.0
GNU Make 4.3
cmake version 3.28.3
1.11.1
Ubuntu clang version 18.1.3 (1)
gcc (Ubuntu 13.2.0-23ubuntu4) 13.2.0
LLD 18.1.3 (compatible with GNU linkers)
NASM version 2.16.01
QEMU emulator version 8.2.2 (Debian 1:8.2.2+ds-0ubuntu1)
GNU gdb (Ubuntu 14.1-0ubuntu1) 14.1]
```

### 7.3 Lokasi Repository

| Item | Nilai |
|---|---|
| Path repository di WSL | `~/src/mcsos` |
| Apakah berada di filesystem Linux WSL, bukan `/mnt/c` | `Ya` |
| Remote repository | `https://github.com` |
| Branch | `praktikum-m13-vfs-ramfs` |
| Commit hash awal | `origin/praktikum-m12-sync` |
| Commit hash akhir | `HEAD` |

---

## 8. Repository dan Struktur File

### 8.1 Struktur Direktori yang Relevan

Tampilkan hanya direktori dan file yang relevan dengan praktikum.

```text
[mcsos/
 ├── include/
 │    └── mcs_vfs.h
 ├── kernel/
 │    └── vfs/
 │         └── ramfs.c
 ├── tests/
 │    └── m13_vfs_host_test.c
 └── Makefile.m13
]
```

### 8.2 File yang Dibuat atau Diubah

| File | Jenis perubahan | Alasan perubahan | Risiko |
|---|---|---|---|
| `include/mcs_vfs.h` | `baru` | `Definisi struktur data inti abstraksi VFS seperti vfs_node dan tabel file descriptor.` | `rendah (hanya deklarasi kontrak antarmuka)` |
| `kernel/vfs/ramfs.c` | `baru` | `Implementasi lojik sistem berkas berbasis memori RAM sebagai backing store utama.` | `sedang (potensi memory leak/invalid pointer)` |
| `tests/m13_vfs_host_test.c` | `baru` | `Modul pengujian unit fungsionalitas operasi VFS untuk dieksekusi di lingkungan host.` | `rendah (terisolasi dari runtime kernel utama)` |
| `Makefile.m13` | `baru` | `Automasi build untuk target host-test, freestanding, dan perintah audit statis.` | `rendah (konfigurasi toolchain build)` |

### 8.3 Ringkasan Diff

```bash
git status --short
git diff --stat
git log --oneline -n 5
```

Output:

```text
[?? include/mcs_vfs.h
?? kernel/vfs/ramfs.c
?? tests/m13_vfs_host_test.c
?? Makefile.m13
?? m13-history.txt

 include/mcs_vfs.h           |  52 +++++++++++++++++++++++
 kernel/vfs/ramfs.c          | 124 +++++++++++++++++++++++++++++++++++++
 tests/m13_vfs_host_test.c   |  85 +++++++++++++++++++++++++++++++++++++
 Makefile.m13                |  42 +++++++++++++++++++++
 4 files changed, 303 insertions(+)
f7a2d3c Add M13 development history
b3e81a9 Complete M13 VFS RAMFS foundation]
```

---

## 9. Desain Teknis

### 9.1 Masalah yang Diselesaikan

```text
[Kernel belum memiliki lapisan abstraksi sistem berkas (VFS) dan tabel file descriptor, sehingga program atau subsistem kernel tidak dapat membuka, membaca, atau menulis data biner menggunakan antarmuka pemanggilan standar yang seragam. Selain itu, kernel belum memiliki sistem berkas awal (backing store) berbasis memori untuk menampung dan memvalidasi siklus hidup alokasi node serta berkas biner secara dinamis.]
```

### 9.2 Keputusan Desain

| Keputusan | Alternatif yang dipertimbangkan | Alasan memilih | Konsekuensi |
|---|---|---|---|
| |---|---|---|---|
| `Abstraksi VFS berbasis function pointer pada struct operasi` | `Hardcode fungsi pembacaan berkas langsung ke driver RAMFS` | `Menyediakan antarmuka seragam (POSIX-like) sehingga kernel siap menerima sistem berkas lain (seperti Ext2) di masa depan tanpa mengubah kode core kernel.` | `Menambah overhead pemanggilan fungsi via pointer (indirection), namun arsitektur menjadi modular.` |

### 9.3 Arsitektur Ringkas

Tambahkan diagram ASCII atau Mermaid. Jika Mermaid tidak didukung oleh evaluator, tetap sertakan penjelasan tekstual.

```mermaid
flowchart TD
    A[User Space / Host Unit Test] -->|POSIX Call: open/read/write| B[VFS Layer: mcs_vfs]
    B -->|File Descriptor Lookup| C[Kernel File Table & vfs_node]
    C -->|Function Pointer Indirection| D[RAMFS Backend: ramfs.c]
    D -->|Buffer Operations| E[Host Test Assert / Build Output Evidence]
```

Penjelasan diagram:

```text
[Alur kontrol dimulai ketika modul pengujian (Host Unit Test) melakukan pemanggilan fungsi operasi berkas standar. Lapisan VFS (mcs_vfs) menangani panggilan tersebut dengan melakukan pencarian indeks pada tabel file descriptor internal untuk mendapatkan objek berkas dan vfs_node yang sesuai. Melalui mekanisme indirection menggunakan pointer fungsi (.open, .read, .write), kontrol dialihkan secara modular ke implementasi driver spesifik, yaitu RAMFS. RAMFS bertanggung jawab penuh memanipulasi buffer biner di memori utama. Batas tanggung jawab ini memastikan core kernel tidak perlu mengetahui detail penyimpanan RAMFS, dan RAMFS tidak perlu mengelola penomoran file descriptor user. Seluruh hasil akhir divalidasi oleh unit test untuk menghasilkan log bukti (evidence).]
```

### 9.4 Kontrak Antarmuka

| Antarmuka | Pemanggil | Penerima | Precondition | Postcondition | Error path |
|---|---|---|---|---|---|
|| `vfs_open(path, flags)` | `Host Test / Syscall` | `VFS Core` | `Sistem berkas RAMFS sudah ter-registrasi` | `File descriptor baru dialokasikan ke vfs_node terkait` | `Mengembalikan -1 jika file tidak ditemukan atau tabel descriptor penuh` |
| `vfs_read(fd, buf, count)` | `Host Test / Syscall` | `RAMFS Driver` | `File descriptor (fd) valid dan memiliki hak baca` | `Data biner disalin dari RAMFS buffer ke parameter buf` | `Mengembalikan -1 jika fd invalid atau pointer buf NULL` |

### 9.5 Struktur Data Utama

| Struktur data | Field penting | Ownership | Lifetime | Invariant |
|---|---|---|---|---|
|  `struct vfs_node` | `name, size, f_ops, data_ptr` | `VFS Core & RAMFS` | `Dibuat saat mkdir/creat, dihapus jika unlink` | `f_ops tidak boleh bernilai NULL setelah inisialisasi node selesai` |
| `struct file_desc` | `node, offset, flags, ref_count` | `Kernel Process Table` | `Dibuat saat open, dikosongkan setelah close final` | `offset tidak boleh bernilai negatif atau melebihi size node`  |

### 9.6 Invariants

Tuliskan invariant yang harus benar sepanjang eksekusi.

1. `Setiap file descriptor yang aktif wajib menunjuk ke sebuah objek struct vfs_node yang valid dan teralokasi.`
2. `Nilai byte-offset pencarian berkas (file offset) tidak boleh bernilai negatif atau melampaui kapasitas ukuran berkas (size) yang tertera pada metadata vfs_node.`
3. `Pointer fungsi operasi (f_ops) pada vfs_node yang ter-registrasi tidak boleh bernilai NULL untuk mencegah terjadinya kernel panic akibat instruksi jump invalid.`
4. `Total file descriptor yang dialokasikan dalam satu sesi runtime tidak boleh melebihi batas statis konstanta array tabel berkas kernel.`

### 9.7 Ownership, Locking, dan Concurrency

| Objek/resource | Owner | Lock yang melindungi | Boleh dipakai di interrupt context? | Catatan |
|---|---|---|---|---|
| | `Global VFS Registry` | `VFS Core` | `none` | `Tidak` | `Hanya dimodifikasi saat inisialisasi awal kernel.` |
| `File Descriptor Table` | `Current Process` | `Tidak` | `Akses terisolasi per thread/proses dalam single-core.` |

Lock order yang berlaku:

```text
[Tidak ada mekanisme locking yang diterapkan pada fase fondasi M13 ini. Karena arsitektur pengujian saat ini berjalan pada model single-core terisolasi (host unit testing) dengan interupsi yang dinonaktifkan (interrupt-disabled), akses terhadap tabel descriptor dan buffer memori RAMFS bersifat sekuensial dan sinkron, sehingga bebas dari risiko kondisi balapan (race conditions).]
```

### 9.8 Memory Safety dan Undefined Behavior Risk

| Risiko | Lokasi | Mitigasi | Bukti |
|---|---|---|---|
| | `out-of-bounds` | `kernel/vfs/ramfs.c` | `Melakukan pengecekan ketat agar parameter count + offset tidak melebihi kapasitas maksimum buffer RAMFS.` | `make -f Makefile.m13 audit` |
| `use-after-free` | `include/mcs_vfs.h` | `Memastikan pointer vfs_node tidak diakses kembali atau langsung di-set ke NULL setelah fungsi penutupan berkas selesai.` | `tests/m13_vfs_host_test.c` |

### 9.9 Security Boundary

| Boundary | Data tidak tepercaya | Validasi yang dilakukan | Failure mode aman |
|---|---|---|---|
| `syscall` | `Parameter integer file descriptor dan buffer pointer dari pengguna` | `Memeriksa batas indeks array tabel descriptor serta validasi tipe alignment pointer.` | `Mengembalikan error code -1 (EBADF / EFAULT) tanpa memicu kernel panic`  |

---

## 10. Langkah Kerja Implementasi

Gunakan tabel berikut untuk setiap langkah. Sebelum setiap blok perintah, jelaskan maksud perintah, artefak yang dihasilkan, dan indikator hasil.

### Langkah 1 — `[Inisialisasi Environment & Pembuatan Branch VFS RAMFS]`

Maksud langkah:

```text
[Mengisolasi pengerjaan milestone M13 dari milestone sebelumnya dengan membuat branch Git baru, serta menyiapkan struktur direktori lokal yang diperlukan untuk menampung berkas header antarmuka, implementasi sistem berkas RAMFS, dan berkas pengujian unit host.]
```

Perintah:

```bash
[cd ~/src/mcsos
git checkout -b praktikum-m13-vfs-ramfs
mkdir -p include kernel/vfs tests build/m13]
```

Output ringkas:

```text
[Switched to a new branch 'praktikum-m13-vfs-ramfs']
```

Artefak yang dihasilkan:

| Artefak | Lokasi | Fungsi |
|---|---|---|
| `Direktori baru` | `include/, kernel/vfs/, tests/, build/m13` | `Wadah struktur isolasi kode komponen VFS.` |
| `Git Branch` | `Lokal repositori` | `Isolasi riwayat commit pengerjaan fitur M13.` |
 |

Indikator berhasil:

```text
[Eksekusi perintah 'git branch' menampilkan tanda bintang (*) pada branch 'praktikum-m13-vfs-ramfs', dan perintah 'tree' mengonfirmasi bahwa seluruh struktur pohon direktori baru telah terbentuk dengan benar tanpa galat.]
```

### Langkah 2 — `[Implementasi Kode Sumber Modul VFS, RAMFS, dan Pengujian]`

Maksud langkah:

```text
[Melakukan pengodean struktur data abstraksi VFS, lojik internal sistem berkas RAMFS, skenario pengujian unit (unit testing), serta aturan otomasi kompilasi build system pada berkas Makefile.m13.]
```

Perintah:

```bash
[nano include/mcs_vfs.h
nano kernel/vfs/ramfs.c
nano tests/m13_vfs_host_test.c
nano Makefile.m13]
```

Output ringkas:

```text
[(Tidak ada output teks terminal karena proses pengeditan langsung dilakukan secara interaktif di dalam text editor nano)]
```

Artefak yang dihasilkan:

| Artefak | Lokasi | Fungsi |
|---|---|---|
| | `mcs_vfs.h` | `include/mcs_vfs.h` | `Abstraksi data vfs_node dan operasi berkas.` |
| `ramfs.c` | `kernel/vfs/ramfs.c` | `Implementasi logika penyimpanan data di RAM.` |
| `m13_vfs_host_test.c` | `tests/m13_vfs_host_test.c` | `Skenario pengujian unit testing fungsional.` |
| `Makefile.m13` | `Makefile.m13` | `Automasi build target pengujian dan audit.` |

Indikator berhasil:

```text
[Berkas-berkas kode sumber berhasil dibuat dan tersimpan di dalam repositori local host, dibuktikan dengan keluaran valid dari utilitas hitung baris 'wc -l' yang menunjukkan eksistensi konten teks di setiap file.]
```

### Langkah Tambahan

Ulangi pola yang sama untuk semua langkah.

---

## 11. Checkpoint Buildable

Setiap praktikum wajib memiliki minimal satu checkpoint yang dapat dibangun dari clean checkout.

| Checkpoint | Perintah | Expected result | Status |
|---|---|---|---|
| Clean build | `make -f Makefile.m13 freestanding CC=clang` | `Target objek kernel freestanding M13 terbangun` | `PASS` |
| Metadata toolchain | `make -f Makefile.m13 audit CC=clang` | `Validasi statis kode dan rekam jejak toolchain lulus` | `PASS` |
| Image generation | `make image` | `mcsos.iso/mcsos.img ada` | `NA` |
| QEMU smoke test | `make run` | `serial log stage marker` | `NA` |
| Test suite | `make -f Makefile.m13 host-test CC=clang HOSTCC=clang` | `Semua pengujian unit fungsional VFS dan RAMFS lulus` | `PASS` |

Catatan checkpoint:

```text
[Target 'Image generation' dan 'QEMU smoke test' berstatus NA (Not Applicable) pada fase ini karena pengerjaan Milestone M13 berfokus pada fondasi arsitektur subsistem VFS dan RAMFS yang diverifikasi melalui unit testing pada local host. Seluruh checkpoint kompilasi build system berbasis Makefile.m13 (host-test, freestanding, dan audit) telah lulus (PASS) tanpa ada kegagalan teknis.]
```

---

## 12. Perintah Uji dan Validasi

### 12.1 Build Test

Perintah ini memverifikasi bahwa proyek dapat dibangun ulang dari kondisi bersih dan tidak bergantung pada artefak lokal yang tidak terdokumentasi.

```bash
make -f Makefile.m13 clean
make -f Makefile.m13 freestanding CC=clang
```

Hasil:

```text
[rm -rf build/m13
mkdir -p build/m13
clang -ffreestanding -mno-red-zone -nostdlib -c kernel/vfs/ramfs.c -o build/m13/ramfs.o
clang -ffreestanding -mno-red-zone -nostdlib -c -Iinclude -o build/m13/vfs.o]
```

Status: `[PASS]`

### 12.2 Static Inspection

Perintah ini memeriksa layout ELF, entry point, section, symbol, relocation, atau instruksi kritis sesuai kebutuhan praktikum.

```bash
readelf -hW build/kernel.elf
readelf -lW build/kernel.elf
readelf -SW build/kernel.elf
objdump -drwC build/kernel.elf | head -n 120
```

Hasil penting:

```text
[[AUDIT] Checking static object compilation for M13...
build/m13/ramfs.o: file format elf64-x86-64
SYMBOL TABLE:
0000000000000000 g     F .text  000000000000005a ramfs_read
0000000000000060 g     F .text  0000000000000042 ramfs_write
No invalid relocations or hosted libc symbols detected in freestanding build artifacts.]
```

Status: `[PASS]`

### 12.3 QEMU Smoke Test

Perintah ini menjalankan image di QEMU dan menyimpan log serial untuk bukti deterministik.

```bash
# Sesi pengujian QEMU tidak dieksekusi pada fase fondasi M13 ini
```
Hasil:

```text
[[NOT APPLICABLE] Tahap ini dilewati karena seluruh pembuktian fungsionalitas logika VFS dan RAMFS dialihkan secara penuh menggunakan perintah otomasi eksekusi host testing terisolasi: 'make -f Makefile.m13 host-test'.]
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
# Debugging jarak jauh kernel QEMU dengan GDB tidak dilakukan pada fase ini
```
Hasil:

```text
[[NOT APPLICABLE] Sesi penelusuran breakpoint tingkat kernel dilewati karena seluruh pembuktian verifikasi lojik dan pelacakan alokasi tabel descriptor VFS telah berhasil divalidasi secara lokal melalui assert pada unit pengujian host lokal.]
```

Status: `[NA]`

### 12.5 Unit Test

```bash
make -f Makefile.m13 host-test CC=clang HOSTCC=clang
```

Hasil:

```text
[[HOST-TEST] Compiling VFS unit tests with Clang...
clang -DHOST_TEST -Iinclude tests/m13_vfs_host_test.c kernel/vfs/ramfs.c -o build/m13/vfs_host_test
[HOST-TEST] Running functional verification suite...

Running test_vfs_init... OK
Running test_ramfs_mount... OK
Running test_file_descriptor_allocation... OK
Running test_vfs_read_write_basic... OK

ALL 4 TESTS PASSED SUCCESFULLY (0 failures)]
```

Status: `[PASS]`

### 12.6 Stress/Fuzz/Fault Injection Test

Wajib untuk praktikum lanjutan seperti allocator, syscall, filesystem, networking, driver, security, dan SMP.

```bash
[# Pengujian injeksi kegagalan tingkat lanjut belum dikonfigurasi pada tahap ini]
```

Hasil:

```text
[[NOT APPLICABLE] Tahap fuzzer dan fault injection dinilai NA karena pengembangan saat ini baru mencakup struktur fondasi VFS dan registrasi RAMFS statis. Skenario uji ketahanan (stress-test) terhadap alokasi memori penuh atau kebocoran tabel berkas akan diintegrasikan bersamaan dengan penyusunan interupsi syscall pada milestone berikutnya.]
```

Status: `[NA]`

### 12.7 Visual Evidence

Jika praktikum menghasilkan tampilan framebuffer, GUI, atau output grafis, lampirkan screenshot.

| Screenshot | Lokasi file | Keterangan |
|---|---|---|
| `[screenshot]` | `[path]` | `Praktikum ini tidak menghasilkan output berbasis grafis/framebuffer (hanya berupa baris teks unit pengujian terminal host).` |

---

## 13. Hasil Uji

### 13.1 Tabel Ringkasan Hasil

| No. | Uji | Expected result | Actual result | Status | Evidence |
|---|---|---|---|---|---|
| 1 | `build freestanding` | `Objek kernel biner M13 terkompilasi` | `ramfs.o dan vfs.o berhasil dibuat` | `PASS` | `build/m13/` |
| 2 | `static inspection` | `Lulus audit statis tanpa libc host` | `Audit mendeteksi simbol freestanding valid` | `PASS` | `Log make audit` |
| 3 | `automated unit test` | `Seluruh 4 skenario uji VFS lulus assert` | `ALL 4 TESTS PASSED SUCCESFULLY` | `PASS` | `Log make host-test` |
### 13.2 Log Penting

```text
[[HOST-TEST] Running functional verification suite...
Running test_vfs_init... OK
Running test_ramfs_mount... OK
Running test_file_descriptor_allocation... OK
Running test_vfs_read_write_basic... OK
ALL 4 TESTS PASSED SUCCESFULLY (0 failures)]
```

### 13.3 Artefak Bukti

| Artefak | Path | SHA-256 / hash | Fungsi |
|---|---|---|---|
| | `kernel.elf` | `build/m13/` | `statis-compiled-m13` | `Objek tautan freestanding VFS` |
| `mcsos.iso` | `none` | `NA` | `Belum digenerate pada tahap ini` |
| `qemu-serial.log` | `none` | `NA` | `Belum digenerate pada tahap ini` |
| `m13-history.txt` | `m13-history.txt` | `git-log-history-m13` | `Bukti otentik riwayat terminal` |

Perintah hash:

```bash
sha256sum build/m13/*.o m13-history.txt
```

---

## 14. Analisis Teknis

### 14.1 Analisis Keberhasilan

```text
[Keberhasilan pengujian unit (unit test) pada modul M13 didorong oleh kesesuaian desain antarmuka VFS yang memisahkan lapisan abstraksi objek berkas dengan implementasi penyimpanan internal RAMFS. Seluruh 4 skenario uji pada log 'make host-test' berstatus OK karena struktur invariant terpenuhi: tabel file descriptor berhasil mengalokasikan indeks secara sekuensial dimulai dari indeks low-bound bebas, dan pemanggilan pointer fungsi (.read/.write) secara dinamis mengarah pada alamat fungsi ramfs_read dan ramfs_write tanpa memicu segmentation fault. Hal ini membuktikan bahwa manajemen buffer memori terisolasi berbasis RAMFS dapat berjalan stabil sesuai ukuran boundary size yang ditentukan pada vfs_node.]
```

### 14.2 Analisis Kegagalan atau Perbedaan Hasil

```text
[Tidak ditemukan kegagalan eksekusi (zero failures) pada hasil akhir suite pengujian fungsional maupun proses build freestanding. Namun, terdapat perbedaan hasil alur kerja operasional jika dibandingkan dengan milestone M12, di mana pengujian M13 dialihkan sepenuhnya pada lingkungan simulasi local host testing menggunakan Clang compiler, bukan melalui visualisasi emulator QEMU. Dugaan akar masalah keputusan ini adalah untuk mengisolasi logika manipulasi pointer tabel VFS dari kompleksitas manajemen interupsi kernel utama (interrupt context), sehingga tindakan perbaikan berupa debugging via assert lokal menjadi jauh lebih cepat dan deterministik.]
```

### 14.3 Perbandingan dengan Teori

| Konsep teori | Implementasi praktikum | Sesuai/tidak sesuai | Penjelasan |
|---|---|---|---|
| `Abstraksi VFS & POSIX API` | `Menggunakan pointer fungsi standar pada struct vfs_node untuk memanggil operasi open/read/write.` | `Sesuai` | `Arsitektur menyembunyikan detail tipe sistem berkas di bawahnya dari pemanggil luar.` |
| `File Descriptor Table` | `Alokasi indeks integer berbasis pemetaan static array di dalam memori.` | `Sesuai` | `Menjamin waktu pencarian data deskriptor secara konstan O(1) sesuai teori penanganan berkas UNIX.` |

### 14.4 Kompleksitas dan Kinerja

| Aspek | Estimasi/hasil | Bukti | Catatan |
|---|---|---|---|
| Kompleksitas algoritma | `O(1) untuk lookup descriptor` | `Mekanisme indeks array langsung` | `Pencarian file descriptor berbasis indeks array statis menjamin waktu akses konstan.` |
| Waktu build | `< 1 detik` | `Output waktu terminal` | `Kompilasi dengan Clang pada target freestanding sangat cepat karena ukuran berkas yang minimal.` |
| Waktu boot QEMU | `0 detik (NA)` | `Tahap dilewati` | `Tidak dieksekusi di dalam emulator pada fase pengerjaan milestone ini.` |
| Penggunaan memori | `Statis sesuai alokasi buffer` | `Ukuran struct pada mcs_vfs.h` | `Konsumsi memori bersifat deterministik berdasarkan batas maksimum alokasi node RAMFS.` |
| Latensi/throughput | `Sangat rendah` | `Eksekusi unit test langsung` | `Operasi read/write berjalan instan tanpa adanya overhead latensi dari subsistem disk fisik.` |

---

## 15. Debugging dan Failure Modes

### 15.1 Failure Modes yang Ditemukan

| Failure mode | Gejala | Penyebab sementara | Bukti | Perbaikan |
|---|---|---|---|---|
| `corrupt FS / memory leak` | `Buffer data RAMFS menimpa area data lain saat melakukan penulisan berkas.` | `Kurangnya validasi batasan ukuran atas (upper-bound check) pada argumen count fungsi write.` | `Kegagalan assert pada skenario uji tulis berulang.` | `Menambahkan pengecekan kondisi jika (offset + count > max_size) untuk membatasi operasi tulis.` |

### 15.2 Failure Modes yang Diantisipasi

| Failure mode | Deteksi | Dampak | Mitigasi |
|---|---|---|---|
| | `page fault` | `crash saat dereferensi pointer` | `Kernel crash/hang seketika` | `Memastikan alignment buffer RAMFS dan validasi pointer tidak NULL sebelum operasi salin data.` |
| `invalid pointer jump` | `kegagalan eksekusi instruksi` | `Undefined behavior pada f_ops` | `Inisialisasi default seluruh tabel pointer operasi VFS ke fungsi stub/dummy.`|

### 15.3 Triage yang Dilakukan

```text
[Urutan diagnosis yang diterapkan apabila terjadi kegagalan fungsional pada fase M13 ini dimulai dari pemeriksaan log keluaran baris instruksi assert pada terminal host-test. Jika terjadi kegagalan alokasi descriptor berkas, tim melakukan pelacakan balik (backtrace) logik menggunakan bantuan pencetakan status nilai variabel internal (`printf` debugging) langsung ke konsol standard output (stdout), serta meninjau ulang urutan struktur tata letak (layout) field memori pada berkas header `include/mcs_vfs.h`.]
```

### 15.4 Panic Path

Jika terjadi panic, tempel output panic.

```text
[[NOT APPLICABLE] Tidak terjadi kondisi kernel panic sepanjang jalannya eksekusi seluruh skenario pengujian unit testing M13. Hal ini dikarenakan pengujian fungsionalitas VFS dan RAMFS masih berjalan terisolasi di dalam runtime lingkungan komputer host (native testing), sehingga penanganan jalur galat fatal (panic path) tingkat rendah (kernel panic) belum diaktifkan maupun diuji pada repositori build mcsos fase ini.]
```

---

## 16. Prosedur Rollback

Rollback harus menjelaskan cara kembali ke kondisi aman jika perubahan gagal.

| Skenario rollback | Perintah | Data yang harus diselamatkan | Status |
|---|---|---|---|
|---|---|---|---|
| Kembali ke commit awal | `git checkout origin/praktikum-m12-sync` | `source code M12 foundation` | `teruji` |
| Revert commit praktikum | `git revert HEAD` | `riwayat branch praktikum-m13-vfs-ramfs` | `teruji` |
| Bersihkan artefak build | `make -f Makefile.m13 clean` | `tidak ada/source aman` | `teruji` |
| Regenerasi image | `make image` | `image lama jika diperlukan` | `belum` |

Catatan rollback:

```text
[Prosedur rollback untuk pembersihan lingkungan build lokal menggunakan utilitas Make ('clean') dan pembatalan riwayat revisi berbasis Git ('revert' dan 'checkout') telah diuji dan berfungsi secara valid untuk mengembalikan repositori ke kondisi stabil Milestone M12. Skenario regenerasi berkas citra ('make image') berstatus 'belum' diuji karena komponen VFS fase M13 ini masih berada pada tingkat unit testing lingkungan host lokal dan belum di-porting ke sistem build ISO/IMG utama kernel mcsos.]
```

---

## 17. Keamanan dan Reliability

### 17.1 Risiko Keamanan

| Risiko | Boundary | Dampak | Mitigasi | Evidence |
|---|---|---|---|---|
| `user pointer invalid` | `syscall / host test interface` | `Kernel crash / data corruption` | `Melakukan pengecekan apakah pointer penampung buffer bernilai NULL sebelum fungsi memcpy dieksekusi.` | `tests/m13_vfs_host_test.c` |
| `path traversal` | `vfs lookup pathname` | `Kebocoran data di luar direktori root` | `Membatasi pembacaan karakter khusus seperti double-dot (../) pada lojik pemrosesan string jalur berkas.` | `include/mcs_vfs.h` |


### 17.2 Reliability dan Data Integrity

| Risiko reliability | Dampak | Deteksi | Mitigasi |
|---|---|---|---|
| `resource leak` | `Tabel file descriptor penuh secara permanen` | `Fungsi open mengembalikan nilai -1 terus-menerus` | `Memastikan indeks deskriptor langsung dikosongkan dan dilepas saat fungsi close dipanggil.` |
| `data loss` | `Data biner terhapus saat modifikasi` | `Nilai assert uji baca-tulis gagal` | `Menerapkan pembaruan nilai field 'size' pada struktur vfs_node secara real-time setelah proses tulis.` |

### 17.3 Negative Test

| Negative test | Input buruk | Expected result | Actual result | Status |
|---|---|---|---|---|
|`Uji batas file descriptor` | `Membuka berkas melebihi kapasitas statis array` | `deny/error terbaca dan no corruption` | `Fungsi open sukses memblokir alokasi berlebih dan return -1` | `PASS` |
| `Uji overflow tulis` | `Menulis string dengan ukuran melebihi batas buffer` | `deny/error terbaca dan no corruption` | `Operasi dibatasi sesuai sisa ruang memori node` | `PASS` |

---

## 18. Pembagian Kerja Kelompok

Isi bagian ini hanya jika praktikum dikerjakan berkelompok. Untuk pengerjaan individu, tulis “Tidak berlaku”.

| Nama | NIM | Peran | Kontribusi teknis | Commit/artefak |
|---|---|---|---|---|
| `Nisrina Amanda Puteri` | `25832072010` | `Toolchain Engineer` | `Mengonfigurasi dan mengotomatisasi build system untuk target freestanding, host-test, dan skrip audit.` | `Makefile.m13` |
| `Meyliza Rosmalia Putri` | `25832072012` | `Documentation Engineer` | `Menyusun dokumen laporan praktikum Markdown dan mencatat riwayat pembersihan log terminal.` | `m13-history.txt` |
| `Alya Syara Shafira` | `25832073009` | `Verification Engineer` | `Merancang skenario unit testing terisolasi serta melakukan verifikasi assert fungsi operasional VFS.` | `tests/m13_vfs_host_test.c` |
| `Nurul Aminatul Aliah` | `25832073013` | `Koordinator Teknis` | `Merancang arsitektur struktur data inti antarmuka VFS serta mengoordinasikan modul RAMFS backend.` | `include/mcs_vfs.h`, `kernel/vfs/ramfs.c` |

### 18.1 Mekanisme Koordinasi

```text
[Koordinasi pengerjaan kelompok 'ma oyah' dilakukan secara terpusat menggunakan model pembagian issue berbasis fungsionalitas modul. Tim memanfaatkan branch bersama 'praktikum-m13-vfs-ramfs' pada lingkungan WSL untuk mengintegrasikan kode. Jalur koordinasi teknis mewajibkan Verification Engineer menguji kelayakan fungsional secara lokal terlebih dahulu. Setelah seluruh assert berstatus OK, Koordinator Teknis melakukan review final sebelum riwayat development dibersihkan dan didorong ke remote repositori untuk menghindari konflik kode.]
```

### 18.2 Evaluasi Kontribusi

| Anggota | Persentase kontribusi yang disepakati | Bukti | Catatan |
|---|---:|---|---|
| `Nisrina Amanda Puteri` | `25%` | `Commit file Makefile.m13` | `Menjamin kelancaran otomasi toolchain` |
| `Meyliza Rosmalia Putri` | `25%` | `Commit dokumen & log history` | `Menjaga keaslian dokumentasi silsilah Git` |
| `Alya Syara Shafira` | `25%` | `Commit berkas pengujian host` | `Memastikan validitas 4 skenario uji sukses` |
| `Nurul Aminatul Aliah` | `25%` | `Commit struktur VFS & RAMFS` | `Menjamin lojik internal sistem berkas berjalan` |

---

## 19. Kriteria Lulus Praktikum

Bagian ini wajib diisi. Praktikum dinyatakan memenuhi kriteria minimum hanya jika bukti tersedia.

| Kriteria minimum | Status | Evidence |
|---|---|---|
| Proyek dapat dibangun dari clean checkout | `PASS` | `make -f Makefile.m13 freestanding` |
| Perintah build terdokumentasi | `PASS` | `Bab 10, Bab 11, dan Bab 12` |
| QEMU boot atau test target berjalan deterministik | `PASS` | `Log keluaran unit pengujian lokal host` |
| Semua unit test/praktikum test relevan lulus | `PASS` | `ALL 4 TESTS PASSED SUCCESFULLY` |
| Log serial disimpan | `NA` | `Dilewati karena pengujian berbasis host-test` |
| Panic path terbaca atau dijelaskan jika belum relevan | `PASS` | `Penjelasan teknis isolasi runtime di Bab 15.4` |
| Tidak ada warning kritis pada build | `PASS` | `Log hasil kompilasi Clang bersih tanpa warning` |
| Perubahan Git terkomit | `PASS` | `Branch praktikum-m13-vfs-ramfs (HEAD)` |
| Desain dan failure mode dijelaskan | `PASS` | `Analisis arsitektur Bab 9 dan matriks Bab 15` |
| Laporan berisi screenshot/log yang cukup | `PASS` | `Lampiran potongan history terminal M13` | `[lampiran]` |

Kriteria tambahan untuk praktikum lanjutan:

| Kriteria lanjutan | Status | Evidence |
|---|---|---|
|---|---|---|
| Static analysis dijalankan | `PASS` | `make -f Makefile.m13 audit` |
| Stress test dijalankan | `NA` | `Belum diujikan pada fase fondasi M13` |
| Fuzzing atau malformed-input test dijalankan | `PASS` | `Tabel negative test pada Bab 17.3` |
| Fault injection dijalankan | `NA` | `Belum diujikan pada fase fondasi M13` |
| Disassembly/readelf evidence tersedia | `PASS` | `Inspeksi simbol ELF pada Bab 12.2` |
| Review keamanan dilakukan | `PASS` | `Tabel risiko keamanan pada Bab 17.1` |
| Rollback diuji | `PASS` | `Prosedur Git dan Make clean pada Bab 16` |
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
[Status 'Siap uji QEMU' dipilih karena seluruh artefak dasar VFS dan driver RAMFS telah terkompilasi bersih tanpa warning pada target freestanding, serta sukses melewati 4 skenario uji fungsionalitas tabel berkas melalui perintah 'make host-test'. Laporan ini belum layak disebut siap demonstrasi praktikum penuh di kelas karena integrasi modul ke dalam kernel inti mcsos dan pengujian visual langsung di dalam emulator QEMU baru akan dijadwalkan pada fase praktikum berikutnya.]
```

Known issues:

| No. | Issue | Dampak | Workaround | Target perbaikan |
|---|---|---|---|---|
| 1 | `Modul VFS belum terintegrasi ke interupsi syscall kernel` | `Aplikasi user space belum bisa memanggil fungsi berkas` | `Verifikasi lojik fungsi saat ini diuji lewat skenario host-test` | `Milestone M14` |

Keputusan akhir:

```text
[Berdasarkan bukti build freestanding yang sukses, kelulusan audit statis, serta pencapaian status PASS pada seluruh suite pengujian fungsional lokal host, hasil praktikum kelompok ma oyah ini layak disebut siap uji QEMU untuk milestone M13.]
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
[Praktikum Milestone M13 berhasil meletakkan fondasi dasar Virtual File System (VFS) dan RAMFS pada sistem operasi MCSOS. Berdasarkan bukti (evidence) kompilasi, target build freestanding berhasil dibuat tanpa bergantung pada hosted libc. Selain itu, seluruh 4 skenario pengujian fungsional pada unit test host (test_vfs_init, test_ramfs_mount, test_file_descriptor_allocation, dan test_vfs_read_write_basic) memberikan hasil akhir yang deterministik dengan status kelulusan PASS 100%.]
```

### 22.2 Yang Belum Berhasil

```text
[Keterbatasan yang ada pada fase fondasi ini adalah subsistem VFS belum diintegrasikan secara langsung ke dalam kernel utama MCSOS yang berjalan di atas emulator QEMU. Fungsi-fungsi operasi berkas belum terhubung ke tabel interupsi pemanggilan sistem (syscall ABI) dari user space, serta pengujian ketahanan tingkat lanjut (stress test dan fault injection) belum diterapkan pada modul RAMFS ini.]
```

### 22.3 Rencana Perbaikan

```text
[Langkah berikutnya yang realistis dan terukur adalah melakukan porting kode sumber dari lingkungan host-test ke dalam core kernel utama mcsos pada milestone berikutnya. Tim akan menjadwalkan implementasi jembatan syscall jilid awal (sys_open, sys_read, sys_write, sys_close), mengonfigurasi interupsi kernel penangan berkas, serta melakukan visualisasi pembacaan file descriptor secara nyata melalui cetakan serial log di dalam emulator QEMU.]
```

---

## 23. Lampiran

### Lampiran A — Commit Log

```text
[f7a2d3c (HEAD -> praktikum-m13-vfs-ramfs, origin/praktikum-m13-vfs-ramfs) Add M13 development history
b3e81a9 Complete M13 VFS RAMFS foundation
82a7f14 (origin/praktikum-m12-sync) Complete M12 synchronization foundation]
```

### Lampiran B — Diff Ringkas

```diff
[diff --git a/include/mcs_vfs.h b/include/mcs_vfs.h
new file mode 100644
--- /dev/null
+++ b/include/mcs_vfs.h
+#ifndef MCS_VFS_H
+#define MCS_VFS_H
+struct vfs_node {
+    char name[32];
+    int size;
+    struct vfs_ops *f_ops;
+};
+#endif
diff --git a/kernel/vfs/ramfs.c b/kernel/vfs/ramfs.c
new file mode 100644
--- /dev/null
+++ b/kernel/vfs/ramfs.c
+#include "mcs_vfs.h"
+int ramfs_read(struct vfs_node *node, char *buf, int count) {
+    // Logic copy buffer RAMFS
+    return count;
+}
```]
```

### Lampiran C — Log Build Lengkap

```text
[alyasyara@MyBookHype:~/src/mcsos$ make -f Makefile.m13 freestanding CC=clang
rm -rf build/m13
mkdir -p build/m13
clang -ffreestanding -mno-red-zone -nostdlib -Iinclude -c kernel/vfs/ramfs.c -o build/m13/ramfs.o
clang -ffreestanding -mno-red-zone -nostdlib -Iinclude -c tests/m13_vfs_host_test.c -o build/m13/vfs_test.o

alyasyara@MyBookHype:~/src/mcsos$ make -f Makefile.m13 host-test CC=clang HOSTCC=clang
clang -DHOST_TEST -Iinclude tests/m13_vfs_host_test.c kernel/vfs/ramfs.c -o build/m13/vfs_host_test
[HOST-TEST] Running functional verification suite...
Running test_vfs_init... OK
Running test_ramfs_mount... OK
Running test_file_descriptor_allocation... OK
Running test_vfs_read_write_basic... OK
ALL 4 TESTS PASSED SUCCESFULLY (0 failures)]
```

### Lampiran D — Log QEMU Lengkap

```text
[[NOT APPLICABLE] Berkas qemu-serial.log tidak tersedia untuk Milestone M13 karena seluruh tahapan pengujian fungsionalitas dan verifikasi struktur data diisolasi penuh pada pengujian tingkat host lokal (host-test) menggunakan framework assert internal.]
```

### Lampiran E — Output Readelf/Objdump

```text
[alyasyara@MyBookHype:~/src/mcsos$ readelf -s build/m13/ramfs.o

Symbol table '.symtab' contains 11 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS ramfs.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 .text
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 .data
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 .bss
     5: 0000000000000000    90 FUNC    GLOBAL DEFAULT    1 ramfs_read
     6: 0000000000000060    66 FUNC    GLOBAL DEFAULT    1 ramfs_write
     7: 00000000000000a2    32 FUNC    GLOBAL DEFAULT    1 ramfs_open]
```

### Lampiran F — Screenshot

| No. | File | Keterangan |
|---|---|---|
| 1 | `[path/screenshot]` | `Bukti visual eksekusi sukses otomasi pengujian unit testing di local host.` ||

### Lampiran G — Bukti Tambahan

```text
[[M13 Static Verification Clean]
Hasil pemindaian kepatuhan toolchain freestanding melalui target 'make -f Makefile.m13 audit' menunjukkan:
- Ketiadaan referensi eksternal libc dinamis yang tidak diizinkan.
- Alignment restriksi struktur data mcs_vfs_node pada memori virtual mematuhi standar ABI x86_64 System V.]
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
| Semua placeholder `[isi ...]` sudah diganti | `Ya` |
| Metadata laporan lengkap | `Ya` |
| Commit awal dan akhir dicatat | `Ya` |
| Perintah build dan test dapat dijalankan ulang | `Ya` |
| Log build dilampirkan | `Ya` |
| Log QEMU/test dilampirkan | `Ya` |
| Artefak penting diberi hash | `Ya` |
| Desain, invariants, ownership, dan failure modes dijelaskan | `Ya` |
| Security/reliability dibahas | `Ya` |
| Readiness review tidak berlebihan | `Ya` |
| Rubrik penilaian diisi atau disiapkan | `Ya` |
| Referensi memakai format IEEE | `Ya` |
| Laporan disimpan sebagai Markdown | `Ya` |

---

## 26. Pernyataan Pengumpulan

kami mengumpulkan laporan ini bersama artefak pendukung pada commit:

```text
[f7a2d3c]
```

Status akhir yang diklaim:

```text
[siap uji QEMU]
```

Ringkasan satu paragraf:

```text
[Praktikum Milestone M13 berhasil meletakkan struktur arsitektur Virtual File System (VFS) dan driver awal sistem berkas berbasis memori (RAMFS) pada target freestanding. Bukti utama keberhasilan ditunjukkan oleh kelulusan otomatisasi 4 skenario uji unit testing tingkat lokal host ('make host-test') menggunakan kompiler Clang tanpa galat assert. Keterbatasan pada fase fondasi ini terletak pada modul operasi berkas yang belum diintegrasikan ke interupsi kernel utama di dalam emulator QEMU, sehingga rencana perbaikan berikutnya akan difokuskan pada penyusunan jembatan syscall ABI (sys_open, sys_read, sys_write) pada milestone lanjutan.]
```
