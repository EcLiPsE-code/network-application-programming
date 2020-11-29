"use strict"

const socket = new WebSocket('ws://localhost:8080/websocket');
const personalMsgDOM = document.getElementById('personal-msg');
const serverMsgDOM = document.getElementById('server-msg');
const equationCountInputDOM = document.querySelector('input[name="equationCount"]')

function calcSlau() {
    const equationCount = parseInt(equationCountInputDOM.value)
    personalMsgDOM.innerText += 'Client: send equation count ' + equationCount + '\n';
    socket.send('calc: ' + equationCount)
}

socket.onmessage = function (event) {
    serverMsgDOM.innerText += "Server: " + event.data + '\n'
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