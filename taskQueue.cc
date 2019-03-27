#include "taskQueue.h"
#include <stdlib.h>

#define DEFAULT_QUEUE_SIZE 65535

Task_queue_t* queue_create(int size)
{
	// �������нṹ
	Task_queue_t *tq = (Task_queue_t *)malloc(sizeof(Task_queue_t));
	if (tq != nullptr)
	{
		if (size > 0)
		{
			// ��������ṹ
			tq->tasks = (Task_t *)malloc(size * sizeof(Task_t));
			tq->capcity = size;
		}
		else
		{
			int default_size = DEFAULT_QUEUE_SIZE;
			tq->tasks = (Task_t *)malloc(default_size * sizeof(Task_t));
			tq->capcity = default_size;
		}

		if (tq->tasks == nullptr)
		{
			free(tq);
			return nullptr;
		}

		tq->head = tq->tail = tq->size = 0;
	}

	return tq;
}

bool queue_is_full(Task_queue_t* tq)
{
	return tq->size == tq->capcity;
}

bool queue_is_empty(Task_queue_t* tq)
{
	return tq->size == 0;
}

bool queue_push_tail(Task_queue_t* tq, Task_t* t)
{
	if (!queue_is_full(tq))
	{
		tq->tasks[tq->tail].run = t->run;
		tq->tasks[tq->tail].param = t->param;

		//tq->tail++; ����ʾ��  �����޷�����

		// �����������ֵʱ��ȡ����ǰ�������,
		// ������Ҫ����µ�����ʱ���Ը���ǰ�������ṹ
		tq->tail = (tq->tail + 1) % (tq->capcity);
		
		tq->size++;
		return true;
	}

	return false;
}

Task_t* queue_pop_head(Task_queue_t* tq)
{
	Task_t* t = nullptr;
	if (!queue_is_empty(tq))
	{
		t = &(tq->tasks[tq->head]);

		//tq->head--; ���� �����޷�����
		tq->head = (tq->head + 1) % (tq->capcity);

		tq->size--;
	}

	return t;
}

void queue_free(Task_queue_t* tq)
{
	if (tq != nullptr)
	{
		free(tq->tasks);
		free(tq);
	}
}