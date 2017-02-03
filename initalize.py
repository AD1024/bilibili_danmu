import os
import imp


def aioHttpCheck():
    try:
    	imp.find_module('aiohttp')
    except ImportError:
    	print('缺少运行环境，正在安装...')
    	os.system('sudo pip install aiohttp')
    else:
    	print('Everything OK!')
    	os.system('python3 main.py')


if __name__ == '__main__':
	p = os.system('which pip')
	if p != 0:
		print('缺少pip，正在安装...(需要输入密码):')
		os.system('sudo easy_install pip')
		aioHttpCheck()
	else:
		print('pip check: ok')
		aioHttpCheck()
