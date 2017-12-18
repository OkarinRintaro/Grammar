import custom_exception


class Context:
    __level = [0]
    __check = [('0', '0')]

    def verification(self, character):
        temp_level = self.__level[0]
        while temp_level:
            name_var, val_var = self.__check[temp_level]
            if name_var == character:
                return val_var
            temp_level -= 1
        raise custom_exception.CustomException(2)

    def set_variable(self, character, string):
        self.__check.insert(self.__level[0], (character, string))

    def add_bracket_level(self):
        self.__level[0] += 1

    def sub_bracket_level(self):
        self.__level[0] -= 1
