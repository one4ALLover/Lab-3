#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

struct node
{
	char inf[256];  // полезная информация
	struct node* next; // ссылка на следующий элемент 
};

struct node* head = NULL, * last = NULL, * f = NULL; // указатели на первый и последний элементы списка

 //Функции добавления элемента, просмотра списка
void spstore(void), review(void), del(char* name);

char find_el[256];
struct node* find(char* name); // функция нахождения элемента
struct node* get_struct(void); // функция создания элемента

struct node* get_struct(void)
{
	struct node* p = NULL;
	char s[256];

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите название объекта: \n");   // вводим данные
	scanf("%s", s);
	if (*s == 0)
	{
		printf("Запись не была произведена\n");
		return NULL;
	}
	strcpy(p->inf, s);

	p->next = NULL;

	return p;		// возвращаем указатель на созданный элемент
}

/* Последовательное добавление в список элемента (в конец)*/
void spstore(void)
{
	struct node* p = NULL;
	p = get_struct();
	if (head == NULL && p != NULL)	// если списка нет, то устанавливаем голову списка
	{
		head = p;
		last = p;
	}
	else if (head != NULL && p != NULL) // список уже есть, то вставляем в конец
	{
		last->next = p;
		last = p;
	}
	return;
}

/* Просмотр содержимого списка. */
void review(void)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		printf("Имя - %s, \n", struc->inf);
		struc = struc->next;
	}
	return;
}

/* Поиск элемента по содержимому. */
struct node* find(char* name)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		if (strcmp(name, struc->inf) == 0)
		{
			return struc;
		}
		struc = struc->next;
	}
	printf("Элемент не найден\n");
	return NULL;
}

/* Удаление элемента по содержимому. */
void del()
{
	struct node* struc = head; // указатель, проходящий по списку установлен на начало списка
	struct node* prev;// указатель на предшествующий удаляемому элемент
	int flag = 0;      // индикатор отсутствия удаляемого элемента в списке

	if (head == NULL) // если голова списка равна NULL, то список пуст
	{
		printf("Список пуст\n");
		return;
	}

	prev = struc->next;
	head = prev;
	free(struc);
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char choice = '0';
	char name[256];

	while (choice != '5') {
		printf("\nМеню:\n");
		printf("1. Добавить элемент\n");
		printf("2. Просмотреть список\n");
		printf("3. Найти элемент\n");
		printf("4. Удалить элемент\n");
		printf("5. Выйти\n");
		printf("Выберите опцию: ");
		scanf(" %c", &choice);

		switch (choice) {
		case '1':
			spstore();
			break;
		case '2':
			review();
			break;
		case '3':
			printf("Введите имя для поиска: ");
			scanf("%s", name);
			if (find(name)) {
				printf("Элемент найден: Имя - %s\n", name);
			}
			break;
		case '4':
			del();
			break;
		case '5':
			exit(0);
			break;
		default:
			printf("Неверный выбор, попробуйте снова.\n");
		}
	}

	return 0;
}