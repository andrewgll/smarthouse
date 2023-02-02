#!/usr/bin/python3
# -*- coding: utf-8 -*-
import http.server
import subprocess


class CustomHTTPRequestHandler(http.server.BaseHTTPRequestHandler):

    def do_GET(self):

        if self.path == '/run':

            self.send_response(200)
            self.send_header('Content-type', 'text/plain')
            self.end_headers()

            # Execute the other app

            command = 'sudo systemctl start smarthouse.service'
            subprocess.run(command.split())
        if self.path == '/stop':

            self.send_response(200)
            self.send_header('Content-type', 'text/plain')
            self.end_headers()

            command = 'sudo systemctl stop smarthouse.service'
            subprocess.run(command.split())
        else:
            self.send_response(404)
            self.end_headers()


httpd = http.server.HTTPServer(('localhost', 8008),
                               CustomHTTPRequestHandler)
httpd.serve_forever()
