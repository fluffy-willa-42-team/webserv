def get_response(code: int, headers: dict, body: str = ""):
	headers_str = ''
	for key, value in headers.items():
		headers_str += f'{key}: {value}\n'
	headers_str += f'Content-Length: {len(body)}\n'
	res = f'''HTTP/1.1 {code}\n{headers_str}\n{body}'''

	print(res)




code = 200

headers = {}
headers['MyHeader'] = 'Test'

body = 'Hello World'

get_response(code, headers, body)

