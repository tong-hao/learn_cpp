namespace cpp fbthrift.calc

typedef i32 MyInteger
typedef i32 Code
typedef string Message

struct AddRequest{
	1:MyInteger num1,
	2:MyInteger num2
}

struct AddResponse{
	1: Code code;
	2: Message msg;
	3: MyInteger ret;
}


service CalculatorService{
	AddResponse add(1:AddRequest req);
}

