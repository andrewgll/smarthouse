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
            command = 'sudo systemctl start smarthouse.service'
            subprocess.run(command.split())
        if self.path == '/stop':

            self.send_response(200)
            self.send_header('Content-type', 'text/plain')
            self.end_headers()

            command = 'sudo systemctl stop smarthouse.service'
            subprocess.run(command.split())
      


httpd = http.server.HTTPServer(('0.0.0.0', 8008),
                               CustomHTTPRequestHandler)
httpd.serve_forever()
