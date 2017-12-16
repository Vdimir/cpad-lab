const {
  ipcRenderer
} = require('electron')

ipcRenderer.on(
  'opened',
  (event, data, width) => {
    var msg = document.getElementById('helloMessage')
    msg.style.display = "none";
    
    var contentDiv = document.getElementById('content')
    contentDiv.style.display = "block";
    var table = document.getElementById('contentTable')
    table.innerHTML = ""
    for (line of data) {
      let row = table.insertRow()
      for (let i = 0; i < width; i++ ) {
        let cell = row.insertCell()
        cell.innerHTML = line[i] || ""
      }
    }
  })

function onInput(value) {
  ipcRenderer.send('message', value)
}