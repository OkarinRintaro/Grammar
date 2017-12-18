from context import Context
from abc import ABC, abstractmethod
from enum import Enum
import custom_exception


class Operation(Enum):
    ADD_OP = 0
    SUB_OP = 1
    MULT_OP = 2
    DIV_OP = 3


class Expression(ABC):

    def __init__(self):
        self._context = Context()
        super().__init__()

    @abstractmethod
    def calculate(self, info):
        pass


class FuncExp2nd(Expression):
    __arg1, __arg2 = 0.0, 0.0

    def __init__(self, oper):
        self.__op = oper
        super().__init__()

    def calculate(self, info):
        temp = ''
        string = info[0]
        if string[info[1]] != '(':
            raise custom_exception.CustomException(1)
        info[1] += 1
        expres = compare(info)
        if expres != '':
            self.__arg1 = expres.calculate(info)
        else:
            pos = info[1]
            while pos < len(string):
                if string[pos] == ',':
                    self.__arg1 = float(temp)
                    info[1] = pos
                    break
                if ((string[pos] >= 'A' and string[pos] <= 'Z') or (string[pos] >= 'a' and string[pos] <= 'z')):
                    temp += self._context.verification(string[pos])
                if ((string[pos] >= '0' and string[pos] <= '9') or string[pos] == '-' or string[pos] == '.'):
                    temp += string[pos]
                pos += 1
        if string[info[1]] != ',':
                raise custom_exception.CustomException(1)
        info[1] += 1
        expres = compare(info)
        if expres != '':
            self.__arg2 = expres.calculate(info)
        else:
            temp = ''
            pos = info[1]
            while pos < len(string):
                if string[pos] == ')':
                    self.__arg2 = float(temp)
                    info[1] = pos
                    break
                if ((string[pos] >= 'A' and string[pos] <= 'Z') or (string[pos] >= 'a' and string[pos] <= 'z')):
                    temp += self._context.verification(string[pos])
                if ((string[pos] >= '0' and string[pos] <= '9') or string[pos] == '-' or string[pos] == '.'):
                    temp += string[pos]
                pos += 1
        if string[info[1]] != ')':
            raise custom_exception.CustomException(1)
        else:
            info[1] += 1
            if self.__op == Operation.ADD_OP:
                return self.__arg1 + self.__arg2
            if self.__op == Operation.SUB_OP:
                return self.__arg1 - self.__arg2
            if self.__op == Operation.MULT_OP:
                return self.__arg1 * self.__arg2
            if self.__op == Operation.DIV_OP:
                if self.__arg2 == 0:
                    raise custom_exception.CustomException(3)
                return self.__arg1 / self.__arg2


class FuncExp3nd(Expression):
    __arg1, __arg2, __arg3 = ' ', ' ', 0.0

    def __init__(self):
        super().__init__()

    def calculate(self, info):
        string = info[0]
        if string[info[1]] != '(':
            raise custom_exception.CustomException(1)
        self._context.add_bracket_level()
        info[1] += 1
        if ((string[info[1]] >= 'A' and string[info[1]] <= 'Z') or (string[info[1]] >= 'a' and string[info[1]] <= 'z')):
            self.__arg1 = string[info[1]]
            temp = ''
            info[1] += 1
            if string[info[1]] != ',':
                raise custom_exception.CustomException(1)
            info[1] += 1
            expres = compare(info)
            if expres != '':
                self.__arg2 = expres.calculate(info)
            else:
                pos = info[1]
                while pos < len(string):
                    if ((string[pos] >= '0' and string[pos] <= '9') or string[pos] == '-' or string[pos] == '.'):
                        temp += string[pos]
                    else:
                        if string[pos] != ',':
                            raise custom_exception.CustomException(1)
                    if string[pos] == ',':
                        self.__arg2 = temp
                        info[1] = pos
                        break
                    pos += 1
            self._context.set_variable(self.__arg1, self.__arg2)
            info[1] += 1
            expres = compare(info)
            if expres != '':
                self.__arg3 = expres.calculate(info)
            else:
                raise custom_exception.CustomException(1)
            if string[info[1]] != ')':
                raise custom_exception.CustomException(1)
            self._context.sub_bracket_level()
            info[1] += 1
        else:
            raise custom_exception.CustomException(1)
        return self.__arg3


def compare(info):
    string = info[0]
    math_operations = ['add', 'mult', 'div', 'sub', 'let']
    expres = ''
    if string[info[1]:info[1]+3] == math_operations[0]:
        expres = FuncExp2nd(Operation.ADD_OP)
        info[1] += 3
    if string[info[1]:info[1]+4] == math_operations[1]:
        expres = FuncExp2nd(Operation.MULT_OP)
        info[1] += 4
    if string[info[1]:info[1]+3] == math_operations[2]:
        expres = FuncExp2nd(Operation.DIV_OP)
        info[1] += 3
    if string[info[1]:info[1]+3] == math_operations[3]:
        expres = FuncExp2nd(Operation.SUB_OP)
        info[1] += 3
    if string[info[1]:info[1] + 3] == math_operations[4]:
        expres = FuncExp3nd()
        info[1] += 3
    return expres