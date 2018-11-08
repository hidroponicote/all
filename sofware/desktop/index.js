'use strict'
const electron = require('electron')
const {app, BrowserWindow} = electron
const path = require('path')
const url = require('url')
const server = require('./server');

const APP_NAME = 'hidroponicote'

let stateServe = true

//for deploy is necessary to activate the server
let dev = false

//Cuando inicia
app.on('ready', () => {
  try {
    //Run server
    if (stateServe) {
      if (dev) {
        server.dev()
      }
      server.run()
    }
    runDesktop()
    console.log(APP_NAME+' iniciado')
  } catch (e) {
    console.error('Error al iniciar '+APP_NAME+': '+e)
    return
  }

})
app.on('quit', () => {
  try {
    if (stateServe) {
      server.stop()
    }
    console.log(APP_NAME+' finalizado')

  } catch (e) {
    console.error('Error al cerrar '+APP_NAME+': '+e)
    return
  }

})


function runDesktop() {
  //Fullscreem
  const widthScreem = electron.screen.getPrimaryDisplay().workAreaSize.width
  const heightScreem = electron.screen.getPrimaryDisplay().workAreaSize.height
  const iconUrl = url.format({
    pathname: path.join(__dirname, 'assets/icons/win/logo.icns'),
    protocol: 'file:',
    slashes: true
  })
  //Run app
  let mainWindow = new BrowserWindow({
     width: widthScreem,
     height : heightScreem,
     icon: path.join(__dirname, 'assets/icons/png/64x64.png')
  })

  //Show pages
  console.clear()
  console.log('Cargando paginas...       1%');
  try {
      mainWindow.loadURL(`file://${__dirname}/assets/index.html`)
  } catch (e) {
    console.error('Error al mostrar páginas: '+e);
    mainWindow.quit()
    return
  }
  console.clear()
  console.log('Cargando paginas..........100%');
  console.log('Pagina principal cargada con exito');
}
