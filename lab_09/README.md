## Лабораторная работа №9 (`WW_sh_ptr`)

1. Реализовать класс `shared_ptr`, который является умным указателем на матрицу, управляющим
   ее временем жизни. Класс `позволяет` копирование и присваивание.
   Копии указывают на ту же матрицу, что и оригинал.
   Матрица, владение который было передано `shared_ptr`, существует до тех пор,
   пока существует хотя бы один `shared_ptr` который на нее указывает.
   При удалении всех `shared_ptr`, которые владели матрицей, она удаляется.
   Для реализации такой логики используем подсчет ссылок.
