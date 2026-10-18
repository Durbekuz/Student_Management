# Student Management System (C)

Konsol orqali talabalar ro'yxatini boshqarish uchun C tilidagi o'quv loyihasi.

## Imkoniyatlar

- Talaba qo'shish
- Barcha talabalarni ko'rish
- ID, ism yoki guruh bo'yicha qidirish
- Talaba ma'lumotlarini tahrirlash
- Talabani tasdiq bilan o'chirish
- Baholar bo'yicha saralash
- Statistika: soni, o'rtacha, eng yuqori va eng past baho
- `students.txt` fayliga avtomatik saqlash va qayta yuklash
- Kiritilgan ma'lumotlarni tekshirish va takroriy ID ni rad etish

## Talablar

GCC kompilyatori (masalan, MinGW-w64 GCC) va VS Code terminali.

## Kompilyatsiya

Loyiha papkasida terminal oching:

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c student.c storage.c utils.c -o student
```

Windows:

```powershell
.\student.exe
```

Linux/macOS:

```bash
./student
```

## Ma'lumotlar fayli

`students.txt` dastur ishga tushiriladigan joriy papkada avtomatik yaratiladi.
Uni qo'lda tahrirlash tavsiya etilmaydi. Zaxira nusxa olish uchun dasturni yoping
va faylni boshqa joyga ko'chiring.

## Cheklovlar

- Maksimal 1000 ta talaba.
- ID yagona va musbat bo'lishi kerak.
- Yosh 16-100 oralig'ida.
- Baho 0-100 oralig'ida.
- Ism va guruh maydonlarida `|` belgisidan foydalanilmaydi.
- Bu konsol o'quv loyihasi; autentifikatsiya, bir nechta foydalanuvchi va
  ma'lumotlar bazasi hozircha mavjud emas.
