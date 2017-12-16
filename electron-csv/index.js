const {
  app,
  BrowserWindow,
  globalShortcut,
  ipcMain,
  dialog,
  Menu,
} = require('electron')

const path = require('path')
const url = require('url')
var fs = require('fs')

ipcMain.on(
  'message',
  (event, arg) => {
    text = arg
  })

const filters = [{
    name: 'Csv Files',
    extensions: ['csv'],
  },
  {
    name: 'All Files',
    extensions: ['*'],
  },
]

const template = [{
  label: 'File',
  submenu: [{
      label: "Open",
      accelerator: "CommandOrControl+O",
      click: showOpenDialog
    },
    {
      role: 'quit'
    }
  ]
}, {
  label: 'View',
  submenu: [{
      role: 'reload'
    },
    {
      role: 'toggledevtools'
    }
  ]
}, {
  label: 'Help',
  submenu: [{
    label: 'About',
    click() {
      dialog.showMessageBox({
        type: 'info',
        title: 'About',
        message: 'Csv viewer',
        buttons: ['OK']
      })
    }
  }]
}]


function openCsvFile(fname) {
  fs.open(fname, 'r',
    (err, fd) => {
      var bytesRead = 0
      let text = ''
      do {
        const size = 8;
        var buffer = Buffer.alloc(size)
        bytesRead = fs.readSync(fd, buffer, 0, size, null)
        text += buffer
      } while (bytesRead > 0)
      let lines = text.split(/\r\n|\n/).filter(s => s.trim() != "" && !/^#.*$/.test(s))
      let splittedText = lines.map(s => s.split(/,|;/))
      let width = Math.max(...splittedText.map(a => a.length))
      win.webContents.send('opened', splittedText, width)
    })
}

function showOpenDialog() {
  dialog.showOpenDialog({
    filters: filters,
    properties: [dialog.openFile]
  }, (filenames) => {
    if (filenames != undefined && filenames.length > 0)
      openCsvFile(filenames[0])
  })
}

const menu = Menu.buildFromTemplate(template)
Menu.setApplicationMenu(menu)

let win

function createWindow() {
  win = new BrowserWindow({
    width: 800,
    height: 600
  })

  win.loadURL(url.format({
    pathname: path.join(__dirname, 'index.html'),
    protocol: 'file:',
    slashes: true
  }))

  win.on('closed', () => {
    win = null
  })
  // Dont need this because shortcut already setted in meny by 'accelerator' option
  // globalShortcut.register('CommandOrControl+O', showOpenDialog)
}

app.on('ready', createWindow)

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

app.on('activate', () => {
  if (win === null) {
    createWindow()
  }
})