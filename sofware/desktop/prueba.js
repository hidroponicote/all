const nativeImage = require('electron').nativeImage

  let image = nativeImage.createFromPath('/assets/icons/png/logo/64x64.png')
  console.log(image)
