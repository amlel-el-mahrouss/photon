const {
  app,
  BrowserWindow,
  BrowserView,
  WebContentsView,
  screen,
} = require("electron");

const vitoCreateWindow = () => {
  const primaryDisplay = screen.getPrimaryDisplay();
  const { width, height } = primaryDisplay.workAreaSize;

  const win = new BrowserWindow({
    width: width,
    height: height,
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
  toolbar_view.setBounds({ x: 0, y: 0, width: width, height: 60 });
  toolbar_view.webContents.loadFile("../res/toolbar_en.html");

  win.contentView.addChildView(frame_view);
  frame_view.setBounds({ x: 0, y: 60, width: width, height: height - 60 });
  frame_view.webContents.loadFile("../res/home_en.html");

  if (app.commandLine.hasSwitch("vito-sdk")) {
  }
};

app.whenReady().then(() => {
  vitoCreateWindow();
});
