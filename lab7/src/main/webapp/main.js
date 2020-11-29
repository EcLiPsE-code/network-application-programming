"use strict"

const socket = new WebSocket('ws://localhost:8080/websocket');
const personalMsgDOM = document.getElementById('personal-msg');
const serverMsgDOM = document.getElementById('server-msg');
const passwordInputDOM = document.querySelector('input[name="password"]')

function checkPass() {
    const password = passwordInputDOM.value;
    socket.send('check: ' + password)
}

socket.onmessage = function (event) {
    serverMsgDOM.innerText += "Answer server (true-password correct, false-password incorrect): " + event.data + '\n';
}

socket.onopen = function (event) {
    personalMsgDOM.innerText = 'Server: Connected to websocket\n'
}

socket.onclose = function (event) {
    personalMsgDOM.innerText += 'Server: Client disconnected from websocket...\n'
}

socket.onerror = function (event) {
    personalMsgDOM.innerText += 'Server: Client disconnected from websocket...\n'
    personalMsgDOM.innerText += 'error: ' + event.data
}