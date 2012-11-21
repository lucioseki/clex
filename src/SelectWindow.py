from gi.repository import Gtk

class SelectWindow(Gtk.Window):
	def on_button_add_clicked(self, widget):
		self.filechooser = Gtk.FileChooserDialog("Please select files", self, Gtk.FileChooserAction.OPEN, (Gtk.STOCK_CANCEL, Gtk.ResponseType.CANCEL, Gtk.STOCK_OPEN, Gtk.ResponseType.OK))
		self.filechooser.set_select_multiple(self);
		if self.filechooser.run() == Gtk.ResponseType.OK:
			for i in self.filechooser.get_uris():
				self.store.append([i])
		self.filechooser.destroy()
		
	def on_button_cancel_clicked(self, widget):
		self.store.clear()
		self.hide()

	def on_button_ok_clicked(self, widget):
		self.selection_list = []
		for row in self.store:
			self.selection_list.append(row)
		self.hide()

	def get_selection_list(self):
		return self.selection_list

	def on_button_rm_clicked(self, widget):
		iters = [self.treemodel.get_iter(path) for path in self.selected]
		for iter in iters:
			self.treemodel.remove(iter)

	def on_button_clear_clicked(self, widget):
		self.store.clear()

	def on_tree_selection_changed(self, selection):
		self.treemodel, self.selected = selection.get_selected_rows()

	def __init__(self, title):
		Gtk.Window.__init__(self, title=title)
		self.set_default_size(800, 400)

		# containers
		self.mainbox = Gtk.VBox()
		self.listbox = Gtk.HBox()
		self.buttonbox = Gtk.HButtonBox()
		self.buttonbox.set_layout(Gtk.ButtonBoxStyle.START)
		self.listcontrolbox = Gtk.VButtonBox()
		self.listcontrolbox.set_layout(Gtk.ButtonBoxStyle.START)

		# model for the list of files
		self.store = Gtk.ListStore(str)

		# view for the list of files
		self.treeview = Gtk.TreeView(self.store)
		self.renderer = Gtk.CellRendererText()
		self.column = Gtk.TreeViewColumn("Path", self.renderer, text=0)
		self.treeview.append_column(self.column)
		
		self.selection = self.treeview.get_selection()
		self.selection.set_mode(Gtk.SelectionMode.MULTIPLE)
		self.selection.connect("changed", self.on_tree_selection_changed)

		# buttons to control the list
		self.button_add = Gtk.Button(stock=Gtk.STOCK_ADD)
		self.button_rm = Gtk.Button(stock=Gtk.STOCK_REMOVE)
		self.button_clear = Gtk.Button(stock=Gtk.STOCK_CLEAR)

		self.button_add.connect("clicked", self.on_button_add_clicked)
		self.button_rm.connect("clicked", self.on_button_rm_clicked)
		self.button_clear.connect("clicked", self.on_button_clear_clicked)

		self.listcontrolbox.pack_start(self.button_add, True, False, 0)
		self.listcontrolbox.pack_start(self.button_rm, True, False, 0)
		self.listcontrolbox.pack_start(self.button_clear, True, False, 0)
		
		# buttons to commit and to cancel the list
		self.button_ok = Gtk.Button(stock=Gtk.STOCK_OK)
		self.button_cancel = Gtk.Button(stock=Gtk.STOCK_CANCEL)

		self.button_cancel.connect("clicked", self.on_button_cancel_clicked)
		self.button_ok.connect("clicked", self.on_button_ok_clicked)

		self.buttonbox.pack_start(self.button_ok, False, True, 0)
		self.buttonbox.pack_start(self.button_cancel, False, True, 0)

		self.listbox.pack_start(self.treeview, True, True, 0)
		self.listbox.pack_start(self.listcontrolbox, False, True, 0)
		self.mainbox.pack_start(self.listbox, True, True, 0)
		self.mainbox.pack_start(self.buttonbox, False, True, 0)
		self.add(self.mainbox)
