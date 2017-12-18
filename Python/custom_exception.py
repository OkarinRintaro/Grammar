
class CustomException(Exception):

    def __init__(self, er):
        self.__error_code = er

    def what(self):
        if self.__error_code == 1:
            return 'Syntax error!'
        if self.__error_code == 2:
            return 'Undefined variable!'
        if self.__error_code == 3:
            return 'Division by zero!'

        return 'Error!'
