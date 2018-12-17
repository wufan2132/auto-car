#include "Queue.h"

Queue_ Inqueue(u8 Size,u8* P);
BOOL Enqueue(u8  Byte,Queue_* Aim);
BOOL Dequeue(u8* Byte,Queue_* Aim);


Queue_OPS_ Queue_OPS = 
{
	Inqueue,
	Enqueue,
	Dequeue
};

Queue_ Inqueue(u8 Size,u8* P)
{
	Queue_ Aim;
	
	Aim.BUF = P;
	Aim.End = 0;
	Aim.Head = 0;
	Aim.IsEmpty = True;
	Aim.IsFull = False;
	Aim.Length = 0;
	Aim.Size = Size;
	
	return Aim;
};

//Write
BOOL Enqueue(u8 Byte,Queue_* Aim)
{
	u8 Tmp = 0;
	if(Aim->IsFull == False)
	{
		Aim->Length++;
		Tmp = Aim->End;
		Aim->BUF[Tmp] = Byte;
		Tmp++;
		if(Tmp >= Aim->Size) Tmp = 0;
		if(Tmp == Aim->Head) Aim->IsFull = True;
		
		Aim->End = Tmp;
		Aim->IsEmpty = False;
		
		return True;
	}
	return False;
}

//Read
BOOL Dequeue(u8* Byte,Queue_* Aim)
{
	u8 Tmp = 0;
	if(Aim->IsEmpty == False)
	{
		Aim->Length--;
		Tmp = Aim->Head;
		*Byte = Aim->BUF[Tmp];
		Tmp++;
		if(Tmp >= Aim->Size) Tmp = 0;
		if(Tmp == Aim->End) Aim->IsEmpty = True;
		
		Aim->Head = Tmp;
		Aim->IsFull = False;
		
		return True;
	}
	return False;
}

