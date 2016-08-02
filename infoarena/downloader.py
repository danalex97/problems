#!/usr/bin/python
import mechanize
import urllib
import cookielib
import sys
from functools import wraps
import re
from bs4 import BeautifulSoup
import ssl

#Browser
br = mechanize.Browser()

#Cookie Jar
cj = cookielib.LWPCookieJar()
br.set_cookiejar(cj)

#Set browser options
br.set_handle_equiv(True)
br.set_handle_redirect(True)
br.set_handle_referer(True)
br.set_handle_robots(False)

#fake user agent
br.addheaders = [('User-agent', 'Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.0.1) Gecko/2008071615 Fedora/3.0.1-1.fc9 Firefox/3.0.1')]

def login():
    login_url = "https://www.infoarena.ro/"
    br.open(login_url)

    br.select_form(nr = 1)
    br.form['username'] = user
    br.form['password'] = passwd
    res = br.submit()


def get_html(url):
    page = br.open(url)
    return page.read()

def get_soup(url):
    return BeautifulSoup(get_html(url), 'html.parser')

def form_url(url, args):
    e_args = urllib.urlencode(args)
    return url + "?" + e_args

def hrefs(url):
    soup = get_soup(url)
    for a in soup.find_all('a'):
        h = a.get('href')
        yield h


def problems():
    url = utilizator_base + user + "?action=stats"
    for h in hrefs(url):
        m = re.search(r"/problema/(.+)", h)
        if m != None:
            yield m.group(1)


if len(sys.argv) < 3:
    print ("Incorrect arguments\n Correct usage: downloader.py <user> <password>")
    raise Exception("Argument")
else:
    user = sys.argv[1]
    passwd = sys.argv[2]

infoarena_base = "http://www.infoarena.ro"
monitor_base = "http://www.infoarena.ro/monitor"
utilizator_base = "http://www.infoarena.ro/utilizator/"

problems()

def get_source_link(url):
    for h in hrefs(url):
        m = re.search("/job_detail/\d+\?action=view-source", h)
        if m != None:
            return infoarena_base + m.group(0)
    return None

def get_first_source(p):
    for i in xrange(100, 10, -10):
        args = { 'task': p, 'user': user, 'score_begin': i}
        url = form_url(monitor_base, args)
        src = get_source_link(url)
        if src != None:
            return src
    return None

def get_source(url):
    soup = get_soup(url)
    for node in soup.find_all(class_='brush: cpp'):
        return node.get_text()

def process(p):
    url = get_first_source(p)
    if url != None:
        src = get_source(url)
        f = open("src/" + p + ".cpp", "w")
        f.write(src)
        f.close()


login()

for p in problems():
    process(p)
