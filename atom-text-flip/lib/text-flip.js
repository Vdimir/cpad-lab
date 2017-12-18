const {CompositeDisposable} = require('atom')

function changeCase(str) {
  var res = '';
  for (var i = 0; i < str.length; i++) {
      if (str.charAt(i) === str.charAt(i).toLowerCase()) {
          res += str.charAt(i).toUpperCase()
      } else if (str.charAt(i) === str.charAt(i).toUpperCase()) {
          res += str.charAt(i).toLowerCase()
      } else {
          res += str.charAt(i)
      }
  }
  return res;
}


module.exports = {
  subscriptions: null,

  activate () {
    this.subscriptions = new CompositeDisposable()
    
    this.subscriptions.add(atom.commands.add('atom-workspace',
      {'text-flip:reverse': () => this.reverse()})
    )
    this.subscriptions.add(atom.commands.add('atom-workspace',
      {'text-flip:toupper': () => this.toUpper()})
    )
    this.subscriptions.add(atom.commands.add('atom-workspace',
      {'text-flip:tolower': () => this.toLower()})
    )
    this.subscriptions.add(atom.commands.add('atom-workspace',
      {'text-flip:toopposite': () => this.toOppositeCase()})
    )
  },

  deactivate () {
    this.subscriptions.dispose()
  },

  reverse () {
    const editor = atom.workspace.getActiveTextEditor()
    if (editor) {
      const selection = editor.getSelectedText()
      editor.insertText(selection.split("").reverse().join(""))
    }
  },
  
  toLower () {
    const editor = atom.workspace.getActiveTextEditor()
    if (editor) {
      const selection = editor.getSelectedText()
      editor.insertText(selection.toLowerCase())
    }
  },
  
  toUpper () {
    const editor = atom.workspace.getActiveTextEditor()
    if (editor) {
      const selection = editor.getSelectedText()
      editor.insertText(selection.toUpperCase())
    }
  },
  
  toOppositeCase() {
    const editor = atom.workspace.getActiveTextEditor()
    if (editor) {
      const selection = editor.getSelectedText()
      editor.insertText(changeCase(selection))
    }
  }
}
