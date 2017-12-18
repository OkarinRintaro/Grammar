import expression
import custom_exception


info =[]
ex = input('Enter math expression: ')
info.append(ex)
pos = 0
info.append(pos)
try:
    expres = expression.compare(info)
    if expres == '':
        raise custom_exception.CustomException(1)
    else:
        print('Result: ', expres.calculate(info))
except custom_exception.CustomException as e:
    print('exception caught: ', e.what())
