# Copyright 2019 Tihran Katolikian

class FileGenerateHelper:

    def __init__(self, file, tab_string, comment_string):
        
        self.__file = file
        self.__tabs = 0
        self.__is_comment = False
        self.__tab_string = tab_string
        self.__comment_string = comment_string

    def tab(self):
        self.__tabs += 1

    def untab(self):
        if self.__tabs > 0: self.__tabs -= 1

    def set_comment_mode(self, commend_mode):
        self.__is_comment = commend_mode
        
    def put(self, text):
        '''
        Writes text in file according to the state.
        :param text: the text;
        :type text: str.
        '''
        for i in range(self.__tabs):
            self.__file.write(self.__tab_string)

        if self.__is_comment:
            self.__file.write(f'{self.__comment_string} ')

        self.__file.write(text)

    
class IndentIncreaser:

    def __init__(self, file_gen_helper):

        self.__gen_helper = file_gen_helper

    def __enter__(self):
        '''
        Increases the indent
        '''
        self.__gen_helper.tab()

    def __exit__(self, exc_type, exc_val, exc_tb):
        '''
        Decreases the indent
        '''
        self.__gen_helper.untab()


class Commenter:

    def __init__(self, file_gen_helper):

        self.__gen_helper = file_gen_helper

    def __enter__(self):
        '''
        Enables the comment mode
        '''
        self.__gen_helper.set_comment_mode(True)

    def __exit__(self, exc_type, exc_val, exc_tb):
        '''
        Disables the comment mode
        '''
        self.__gen_helper.set_comment_mode(False)


class Block:

    def __init__(self, file_gen_helper, block_start, block_end):

        self.__gen_helper = file_gen_helper
        self.__block_start = block_start
        self.__block_end = block_end

    def __enter__(self):
        '''
        Starts the block
        '''
        self.__gen_helper.put(self.__block_start)

    def __exit__(self, exc_type, exc_val, exc_tb):
        '''
        Ends the block
        '''
        self.__gen_helper.put(self.__block_end)
