def get_response(headers: dict, body: str = ""):
	headers_str = ''
	for key, value in headers.items():
		headers_str += f'{key}: {value}\n'

	if (len(body) != 0):
		headers_str += f'Content-Length: {len(body)}\n'
	
	res = f'''{headers_str}\n{body}'''
	print(res)



headers = {}
headers['status'] = '200 OK'
headers['MyHeader'] = 'Test'

body = ''

get_response(headers, body)

