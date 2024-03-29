#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

char *compute_get_request(char *host, char *url, char *query_params,
							char **cookies, int cookies_count, char* auth_token)
{
	char *message = calloc(BUFLEN, sizeof(char));
	char *line = calloc(LINELEN, sizeof(char));

	// Step 1: write the method name, URL, request params (if any) and protocol type
	if (query_params != NULL) {
		sprintf(line, "GET %s?%s HTTP/1.1", url, query_params);
	} else {
		sprintf(line, "GET %s HTTP/1.1", url);
	}

	compute_message(message, line);

	// Step 2: add the host
	sprintf(line, "Host: %s", host);
	compute_message(message, line);

	// Step 3 (optional): add headers and/or cookies, according to the protocol format
	if (cookies_count != 0) {
		sprintf(line, "Cookie: ");
		strcat(message, line);
		for(int i = 0 ; i < cookies_count - 1; i++) {
		   sprintf(line, "%s", cookies[i]);
		   strcat(message, line);
		   strcat(message, "; ");
		}
		sprintf(line, "%s", cookies[cookies_count - 1]);
		compute_message(message, line);
	}

	if (auth_token != NULL) {
		sprintf(line, "Authorization: Bearer %s", auth_token);
		compute_message(message, line);
	}

	// Step 4: add final new line
	compute_message(message, "");

	return message;
}

char *compute_post_request(char *host, char *url, char* content_type, char *body_data,
							 char **cookies, int cookies_count, char* auth_token)
{
	char *message = calloc(BUFLEN, sizeof(char));
	char *line = calloc(LINELEN, sizeof(char));

	// Step 1: write the method name, URL and protocol type
	sprintf(line, "POST %s HTTP/1.1", url);
	compute_message(message, line);
	
	// Step 2: add the host
	sprintf(line, "Host: %s", host);
	compute_message(message, line);

	/* Step 3: add necessary headers (Content-Type and Content-Length are mandatory)
			in order to write Content-Length you must first compute the message size
	*/
	sprintf(line, "Content-Type: %s", content_type);
	compute_message(message, line);

	sprintf(line, "Content-Length: %ld", strlen(body_data));
	compute_message(message, line);

	// Step 4 (optional): add cookies
	if (cookies_count != 0) {
		sprintf(line, "Cookie: ");
		strcat(message, line);
		for(int i = 0 ; i < cookies_count - 1; i++) {
		   sprintf(line, "%s", cookies[i]);
		   strcat(message, line);
		   strcat(message, "; ");
		}
		sprintf(line, "%s", cookies[cookies_count - 1]);
		compute_message(message, line);
	}

	if (auth_token != NULL) {
		sprintf(line, "Authorization: Bearer %s", auth_token);
		compute_message(message, line);
	}

	// Step 6: add the actual payload data
	compute_message(message, "");
	compute_message(message, body_data);

	return message;
}

// Copie a functiei GET, dar pentru DELETE
char *compute_delete_request(char *host, char *url, char *query_params,
							char **cookies, int cookies_count, char* auth_token)
{
	char *message = calloc(BUFLEN, sizeof(char));
	char *line = calloc(LINELEN, sizeof(char));

	// Step 1: write the method name, URL, request params (if any) and protocol type
	if (query_params != NULL) {
		sprintf(line, "DELETE %s?%s HTTP/1.1", url, query_params);
	} else {
		sprintf(line, "DELETE %s HTTP/1.1", url);
	}

	compute_message(message, line);

	// Step 2: add the host
	sprintf(line, "Host: %s", host);
	compute_message(message, line);

	// Step 3 (optional): add headers and/or cookies, according to the protocol format
	if (cookies_count != 0) {
		sprintf(line, "Cookie: ");
		strcat(message, line);
		for(int i = 0 ; i < cookies_count - 1; i++) {
		   sprintf(line, "%s", cookies[i]);
		   strcat(message, line);
		   strcat(message, "; ");
		}
		sprintf(line, "%s", cookies[cookies_count - 1]);
		compute_message(message, line);
	}

	if (auth_token != NULL) {
		sprintf(line, "Authorization: Bearer %s", auth_token);
		compute_message(message, line);
	}

	// Step 4: add final new line
	compute_message(message, "");

	return message;
}