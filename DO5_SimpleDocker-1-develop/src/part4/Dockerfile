FROM nginx:latest

WORKDIR /server

COPY server.c server.c
COPY nginx/nginx.conf /etc/nginx/nginx.conf

RUN apt update && \
    apt install -y spawn-fcgi && \
    apt install -y libfcgi-dev && \
	 apt install -y gcc && \
	 gcc -o server server.c -lfcgi
		
ENTRYPOINT spawn-fcgi -p 8080 ./server && nginx -g 'daemon off;'