#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

struct node
{
	char inf[256];  // полезная информация
	int prior;
	struct node* next; // ссылка на следующий элемент 
};

struct node* head = NULL, * last = NULL, * f = NULL; // указатели на первый и последний элементы списка

// Функции добавления элемента, просмотра списка
void spstore(void), review(void), del(char* name);

char find_el[256];
struct node* find(char* name); // функция нахождения элемента
struct node* get_struct(void); // функция создания элемента

struct node* get_struct(void)
{
	struct node* p = NULL;
	char s[256];
	int prior;

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

	printf("Введите приоритет объекта: \n");
	scanf("%d", &prior);
	p->prior = prior;

	p->next = NULL;

	return p;
}

void spstore(void)
{
	struct node* p = NULL;
	p = get_struct();
	if (head == NULL && p != NULL)
	{
		head = p;
		last = p;
	}
	else if (head != NULL && p != NULL)
	{
		if (head->prior < p->prior) {
			p->next = head;
			head = p;
		}
		else{
			struct node* struc = head;
			while (struc->next != NULL && struc->next->prior >= p->prior)
			{
				struc = struc->next;
			}
			p->next = struc->next;
			struc->next = p;
			if (p->next == NULL) last = p;
		}
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
		printf("Имя - %s, Приоритет - %d \n", struc->inf, struc->prior);
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

///* Удаление элемента по содержимому. */
void del(char* name)
{
	struct node* struc = head; // указатель, проходящий по списку установлен на начало списка
	struct node* prev = NULL;// указатель на предшествующий удаляемому элемент
	int flag = 0;      // индикатор отсутствия удаляемого элемента в списке

	if (head == NULL) // если голова списка равна NULL, то список пуст
	{
		printf("Список пуст\n");
		return;
	}

	if (strcmp(name, struc->inf) == 0) // если удаляемый элемент - первый
	{
		flag = 1;
		head = struc->next; // установливаем голову на следующий элемент
		free(struc);  // удаляем первый элемент
		struc = head; // устанавливаем указатель для продолжения поиска
	}
	else
	{
		prev = struc;
		struc = struc->next;
	}

	while (struc) // проход по списку и поиск удаляемого элемента
	{
		if (strcmp(name, struc->inf) == 0) // если нашли, то
		{
			flag = 1;         // выставляем индикатор
			if (struc->next)  // если найденный элемент не последний в списке
			{
				prev->next = struc->next; // меняем указатели
				free(struc);		    // удаляем  элемент
				struc = prev->next; // устанавливаем указатель для продолжения поиска
			}
			else			// если найденный элемент последний в списке
			{
				prev->next = NULL; // обнуляем указатель предшествующего элемента
				free(struc);	// удаляем  элемент
				return;
			}
		}
		else // если не нашли, то
		{
			prev = struc; // устанавливаем указатели для продолжения поиска
			struc = struc->next;
		}
	}

	if (flag == 0)				// если флаг = 0, значит нужный элемент не найден
	{
		printf("Элемент не найден\n");
		return;
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char choice = '0';
	char name[256];

	while (choice!='5') {
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
			printf("Введите имя для удаления: ");
			scanf("%s", name);
			del(name);
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