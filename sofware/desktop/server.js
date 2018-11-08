'use strict'
const express = require('express');
const bodyParser = require('body-parser');
var fs = require('fs');

var exec = require('child_process').exec, child;

let app = express()

let developer = false


let port = 3000
var run = function() {
  console.log('Server iniciado');
  app.use(bodyParser.json()); // soporte para bodies codificados en jsonsupport
  app.use(bodyParser.urlencoded({ extended: true })); // soporte para bodies codificados

  if (!developer) {
    app.get('/', function (req, res, next) {
      res.send('Sistema hidroponico')
    })
  }

  app.get('/bluetooth', function (req, res, next) {
    res.send('Sistema bluetooth')
  })

  app.get('/bluetooth/devices', function (req, res, next) {
    runCommand('cd scripts && python bt_search_for_devices.py')
    setTimeout(function(){
      var obj;
      fs.readFile('assets/data/devices_aviable.json', 'utf8', function (err, data) {
        if (err) throw err;
        obj = JSON.parse(data);
        res.send(obj)
      });
    }, 12000);

  })

  app.get('/bluetooth/pump/watter/:status', function (req, res, next) {
    if (req.params.status == 'on') {
      try {
        runCommand('cd scripts && python bt_on_watterPumps.py')
        res.send('Bomba de agua iniciada')
      } catch (e) {
        console.log('Error started watter pump. ERROR: ');
        console.log(e);
        next()
      }
    }else if (req.params.status == 'off') {
      try {
        runCommand('cd scripts && python bt_off_watterPumps.py')
        res.send('Bomba de agua apagada')
      } catch (e) {
        console.log('Error started watter pump. ERROR: ');
        console.log(e);
        next()
      }
    }

    console.log('Recibido el parametro: '+ req.params.status);
  })
  // app.get('/bluetooth/pump/watter/off', function (req, res, next) {
  //   runCommand('cd scripts && python bt_off_watterPumps.py')
  //   res.send('Bomba de agua apagada')
  // })

  if (developer) {
    const webpack = require('webpack');
    const webpackDevMiddleware = require('webpack-dev-middleware');

    const config = require('./webpack.config.js');
    const compiler = webpack(config);

    // Tell express to use the webpack-dev-middleware and use the webpack.config.js
    // configuration file as a base.
    app.use(webpackDevMiddleware(compiler, {
      publicPath: config.output.publicPath
    }));
  }
}

var server = app.listen(port, function() {
  if (port === 80) {
    console.log('run server in localhost');
  }
  console.log('run server in localhost:'+port);
})

var stop = function() {
  server.close()
  console.log('Server cerrado');
}

//This method ease developer deployment

var dev = function() {

  developer = true

}

var runCommand = function(command) {
  child = exec(command,
  // Pasamos los parámetros error, stdout la salida
  // que mostrara el comando
    function (error, stdout, stderr) {
      // Imprimimos en pantalla con console.log
      console.log(stdout);
      // controlamos el error
      if (error !== null) {
        console.log('exec error: ' + error);
      }
  });
}

module.exports = {
  run: run,
  server: server,
  app: app,
  stop: stop,
  dev: dev
};
