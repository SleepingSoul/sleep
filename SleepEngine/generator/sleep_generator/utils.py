# Copyright 2019 Tihran Katolikian

from configparser import ConfigParser


CONFIG_FILE = 'config.ini'
ALL_CONFIG = None

def read_all_config():
    '''
    Reads a config for generator. Should be called once.
    '''
    global ALL_CONFIG

    ALL_CONFIG = ConfigParser()

    print('Reading config...')

    try:
        ALL_CONFIG.read(CONFIG_FILE)
    except Exception as e:
        print(f'Failed: {e}\n Stopping script...')
        print('-------------------------------------------')
        return False
    else:
        print('Success.')
        return True

def get_config_section(section_name):
    '''
    Returns a specialized config section.
    :param section_name: a name of section of config;
    :type section_name: str;
    :return: dict-like object with all section data or None;
    :rtype: dict-like object or None.
    '''
    print(f'Looking for section {section_name}...')

    if section_name in ALL_CONFIG.sections():
        print('Success.')
        return ALL_CONFIG[section_name]
    else:
        print(f'Failed: Section {section_name} not found. All sections: {ALL_CONFIG.sections()}\n\
            Stopping script...')
        print('-------------------------------------------')
        return None
