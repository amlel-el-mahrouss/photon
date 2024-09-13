const {
  app,
  BrowserWindow,
  BrowserView,
  WebContentsView,
  contextBridge,
} = require("electron");

const createWindow = () => {
  const win = new BrowserWindow({
    width: 1280,
    height: 720,
    frame: false,
    resizable: false,
    focusable: true,
    titleBarStyle: "hidden",
  });

  const view = new WebContentsView();
  win.contentView.addChildView(view);
  view.setBounds({ x: 0, y: 0, width: 1280, height: 100 });
  view.webContents.loadFile("res/toolbar_en.html");

  const view2 = new WebContentsView();
  win.contentView.addChildView(view2);
  view2.setBounds({ x: 0, y: 100, width: 1280, height: 620 });
  view2.webContents.loadFile("res/home_en.html");
};

app.whenReady().then(() => {
  createWindow();
});
