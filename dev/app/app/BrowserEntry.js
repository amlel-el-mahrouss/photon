const {
  app,
  BrowserWindow,
  BrowserView,
  WebContentsView,
  ipcRenderer,
} = require("electron");

const createWindow = () => {
  const win = new BrowserWindow({
    width: 1280,
    height: 720,
    frame: false,
    resizable: false,
    minWidth: 800,
    minHeight: 600,
    focusable: true,
    titleBarStyle: "hidden",
  });

  const toolbar_view = new WebContentsView();
  const frame_view = new WebContentsView();

  win.contentView.addChildView(toolbar_view);
  toolbar_view.setBounds({ x: 0, y: 0, width: 1280, height: 110 });
  toolbar_view.webContents.loadFile("../res/toolbar_en.html");

  win.contentView.addChildView(frame_view);
  frame_view.setBounds({ x: 0, y: 110, width: 1280, height: 620 });
  frame_view.webContents.loadFile("../res/home_en.html");
};

app.whenReady().then(() => {
  createWindow();
});
