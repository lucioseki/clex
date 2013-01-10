from gi.repository import Gtk

class FileList(Gtk.HBox):
	def __init__(self, string):
		Gtk.HBox.__init__(self)

		self.listcontrolbox = Gtk.VButtonBox()
		self.listcontrolbox.set_layout(Gtk.ButtonBoxStyle.START)

		# model for the list of files
		self.store = Gtk.ListStore(str)

		# view for the list of files
		self.treeview = Gtk.TreeView(self.store)
		self.renderer = Gtk.CellRendererText()
		self.column = Gtk.TreeViewColumn(string + " file name", self.renderer, text=0)
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
		
		self.pack_start(self.treeview, True, True, 0)
		self.pack_start(self.listcontrolbox, False, True, 0)

	def on_tree_selection_changed(self, selection):
		self.treemodel, self.selected = selection.get_selected_rows()

	def on_button_add_clicked(self, widget):
		self.filechooser = Gtk.FileChooserDialog("Please select files", None, Gtk.FileChooserAction.OPEN, (Gtk.STOCK_CANCEL, Gtk.ResponseType.CANCEL, Gtk.STOCK_OPEN, Gtk.ResponseType.OK))
		self.filechooser.set_select_multiple(self);
		if self.filechooser.run() == Gtk.ResponseType.OK:
			for i in self.filechooser.get_uris():
				self.store.append([i])
		self.filechooser.destroy()

	def on_button_rm_clicked(self, widget):
		iters = [self.treemodel.get_iter(path) for path in self.selected]
		for iter in iters:
			self.treemodel.remove(iter)

	def on_button_clear_clicked(self, widget):
		self.store.clear()
