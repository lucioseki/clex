from gi.repository import Gtk
from FileList import *

class DataSetWindow(Gtk.Window):

	def get_selection_list(self):
		return self.selection_list

	def on_button_ok_clicked(self, widget):
		self.selection_list = []
		for row in self.listbox.store:
			self.selection_list.append(row)
		self.hide()

	def on_button_cancel_clicked(self, widget):
		self.listbox.store.clear()
		self.hide()

	def __init__(self):
		Gtk.Window.__init__(self, title="Select DataSets")
		self.set_default_size(800, 400)

		# containers
		self.mainbox = Gtk.VBox()
		self.listbox = FileList("DataSet")

		self.buttonbox = Gtk.HButtonBox()
		self.buttonbox.set_layout(Gtk.ButtonBoxStyle.START)

		# buttons to commit and to cancel the list
		self.button_ok = Gtk.Button(stock=Gtk.STOCK_OK)
		self.button_cancel = Gtk.Button(stock=Gtk.STOCK_CANCEL)
		self.button_cancel.connect("clicked", self.on_button_cancel_clicked)
		self.button_ok.connect("clicked", self.on_button_ok_clicked)
		self.buttonbox.pack_start(self.button_ok, False, True, 0)
		self.buttonbox.pack_start(self.button_cancel, False, True, 0)

		self.mainbox.pack_start(self.listbox, True, True, 0)
		self.mainbox.pack_start(self.buttonbox, False, True, 0)
		self.add(self.mainbox)

		self.selection_list = []
