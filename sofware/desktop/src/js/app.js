'use strict'
const APP_NAME = 'hidroponicote'

const toastr = require('toastr');

import '../css/master.css';

import _ from 'lodash'

import Vue from './vue.js'
import Chart from './Chart.js'
import axios from './axios.min.js'

//on ready
Vue.component('welcome-button', {
  template: `
    <span class="dot" id="state">
       <span class="tooltiptext" id="tooltipTextState"></span>
    </span>
    <span class="bluetooth-container" id="bluetooth">
      BT
      <span class="tooltiptext" id="tooltipTextBluetooth"></span>
    </span>
  `
})
var app = new Vue({
  el: '#app',
  data: {
    list1 : [
      { title: 'BOMBAS' },
      { title: 'LUCES' }
    ],
    list2 : [
      { title: 'CONFIG' }
    ],
    title: { mess: 'HOPE' }
  },
})
//app.list1.push({ title: 'Ejemplo' })
document.addEventListener("DOMContentLoaded", function(event) {


  var bluetoothItem = document.querySelector('#bluetooth')
  var watterPumpButtonOn = document.querySelector('#watterPumpOn')
  var watterPumpButtonOff = document.querySelector('#watterPumpOff')

  bluetoothItem.addEventListener("click", function() {
    toastr.info('Por favor espere', 'Buscando dispositivos bluetooth cercanos...', {timeOut: 8000})
    getBluetoothDevices()
  })

  watterPumpButtonOn.addEventListener("click", function() {
    toastr.info('Por favor espere', 'Encendiendo Bomba de agua...', {timeOut: 8000})
    bluetoothWatterPumpsManager("on")
  })

  watterPumpButtonOff.addEventListener("click", function() {
    toastr.info('Por favor espere', 'Apagando Bomba de agua...', {timeOut: 8000})
    bluetoothWatterPumpsManager("off")
  })


});

//Disable labels charts
Chart.defaults.global.legend.display = false;

var state = 'disconnect'
var element
var stateItem = element = document.querySelector('#state');
//toastr configuration
toastr.options.closeButton = true;

//Show state doth
displayDateState()

//Show state viewBluetoothDevices
viewBluetoothDevices()

//Draw charts information
printChart('canvasChart1', [0])
printChart('canvasChart2', [0])
printChart('canvasChart3', [0])
printChart('canvasChart4', [0])

function displayDateState() {
  var tooltipsText = document.querySelector('#tooltipTextState')
  var text = ''
  var title = 'Estado de la conexión con HOPE'
  var time = 500
  if (state == 'off') {
    stateItem.classList.add("dotOff");
    text = "Sistema apagado"
    toastr.warning(text, title, {timeOut: time})
  }else if (state == 'on') {
    stateItem.classList.add("dotOn");
    text = "Sistema encendido "
    toastr.success(text, title, {timeOut: time})
  }else if (state == 'disconnect') {
    stateItem.classList.add("dotDisconn");
    text = "Sistema desconectado "
    toastr.warning(text, title, {timeOut: time})
  }
  tooltipsText.appendChild(document.createTextNode(text));



}

function viewBluetoothDevices() {
  var tooltipsText = document.querySelector('#tooltipTextBluetooth')
  var text = 'Buscar dispositivos'
  tooltipsText.appendChild(document.createTextNode(text));
}


function printChart(objetoDOM, data) {
  var ctx = document.getElementById(objetoDOM);
  var tempSustr = new Chart(ctx, {
      type: 'line',
      data: {
          labels: ["1", "2", "3", "4", "5", "6h"],
          datasets: [{
              data: data,
              backgroundColor: [
                  '#a9cf45',
              ],
              borderColor: [
                  '#588f27',
              ],
              borderWidth: 1
          }]
      },
      options: {
          scales: {
              yAxes: [{
                  ticks: {
                      beginAtZero:true
                  }
              }]
          }
      }
  });
}

function printCont(){
  var element = document.getElementById("title");
  var nodeTitle = document.createTextNode('');
  element.appendChild(nodeTitle);
}

// Want to use async/await? Add the `async` keyword to your outer function/method.
async function getBluetoothDevices(){
  try {
    var devicesNames = []
    const response = await axios.get('http://localhost:3000/bluetooth/devices');
    for (var i = 0; i < response.data.length; i++) {
      devicesNames.push(response.data[i][1]+', ');
      console.log(response.data[i][1]);
      if (response.data[i][0] == '20:15:04:28:37:22') {
        state = 'on'
      }
    }
    toastr.success(devicesNames, devicesNames.length+' Dispositivos encontrados', {timeOut: 10000})
    console.log(response.data)
  } catch (error) {
    console.error(error);
  }
}

async function bluetoothWatterPumpsManager(switchOrd){
  if (switchOrd == "on") {
    try {
      var devicesNames = []
      const response = await axios.get('http://localhost:3000/bluetooth/pump/watter/on');
      if (response.status == 200) {
        setTimeout(function() {
          toastr.success('Bomba de agua encendida')
        },1800)
      }
    } catch (error) {
      console.error(error);
    }
  }else if (switchOrd == "off") {
    try {
      var devicesNames = []
      const response = await axios.get('http://localhost:3000/bluetooth/pump/watter/off');
      if (response.status == 200) {
        setTimeout(function() {
          toastr.success('Bomba de agua apagada')
        },1800)
      }
    } catch (error) {
      console.error(error);
    }
  }

}
