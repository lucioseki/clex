#!/usr/bin/env python
# main loop of the program

from gi.repository import Gtk
from SelectWindow import *
from Clex_module import *
from os import path
from urlparse import urlparse 

class DataSetWindow(SelectWindow):
	def __init__(self):
		SelectWindow.__init__(self, title="Select DataSets")

class RealPartitionWindow(SelectWindow):
	def __init__(self):
		SelectWindow.__init__(self, title="Select Real Partitions")

class GeneratedPartitionWindow(SelectWindow):
	def __init__(self):
		SelectWindow.__init__(self, title="Select Generated Partitions")

class ValidationWindow(Gtk.Window):
	def __init__(self):
		Gtk.Window.__init__(self, title="Select Validation Indexes")

class SimilarityWindow(Gtk.Window):
	def __init__(self):
		Gtk.Window.__init__(self, title="Select Similarity Measures")
		self.similarity = "Euclidean"

		self.set_default_size(300, 200)
		self.box = Gtk.VBox()
		self.bbox = Gtk.HButtonBox(spacing=6)
		self.bbox.set_layout(Gtk.ButtonBoxStyle.START)

		self.store = Gtk.ListStore(str)
		self.store.append(["Euclidean"])
		self.store.append(["Pearson"])

		self.treeview = Gtk.TreeView(self.store)
		self.renderer = Gtk.CellRendererText()
		self.column = Gtk.TreeViewColumn("Similaridade", self.renderer, text=0)
		self.treeview.append_column(self.column)
		self.box.pack_start(self.treeview, True, True, 0)

		self.button_ok = Gtk.Button(stock=Gtk.STOCK_OK)
		self.button_cancel = Gtk.Button(stock=Gtk.STOCK_CANCEL)
		self.button_ok.connect("clicked", self.on_button_ok_clicked)
		self.button_cancel.connect("clicked", self.on_button_cancel_clicked)
		self.bbox.pack_start(self.button_ok, True, True, 0)
		self.bbox.pack_start(self.button_cancel, True, True, 0)
		self.box.pack_start(self.bbox, True, True, 0)
		self.add(self.box)

	def on_button_ok_clicked(self, widget):
		self.selection = self.treeview.get_selection()
		self.model, self.treeiter = self.selection.get_selected()
		self.similarity = self.model[self.treeiter][0]
		self.hide()

	def on_button_cancel_clicked(self, widget):
		self.hide()

	def get_similarity(self):
		return self.similarity

class MainWindow(Gtk.Window):
	def __init__(self):
		# Create a new window
		Gtk.Window.__init__(self, title="Clustering Experimenter")
		
		# Containers
		self.vbox = Gtk.VBox(spacing=6)
		self.hbox = Gtk.HBox(spacing=6)
		self.bbox1 = Gtk.VButtonBox(spacing=6)
		self.bbox2 = Gtk.VButtonBox(spacing=6)
		self.bbox3 = Gtk.HButtonBox(spacing=6)
		self.bbox1.set_layout(Gtk.ButtonBoxStyle.START)
		self.bbox2.set_layout(Gtk.ButtonBoxStyle.START)
		self.bbox3.set_layout(Gtk.ButtonBoxStyle.START)
		self.hbox.pack_start(self.bbox1, True, True, 0)
		self.hbox.pack_start(self.bbox2, True, True, 0)
		self.vbox.pack_start(self.hbox, True, True, 0)
		self.vbox.pack_start(self.bbox3, True, True, 0)
		self.add(self.vbox)

		# Buttons to open other windows
		self.button_dataset = Gtk.Button(label="Set DataSets")
		self.button_real_partition = Gtk.Button(label="Set Real Partitions")
		self.button_generated_partition = Gtk.Button(label="Set Generated Partitions")
		self.button_similarity = Gtk.Button(label="Set Similarity Measure")
		self.button_validation = Gtk.Button(label="Set Validation Indexes")
		self.button_execute = Gtk.Button(stock=Gtk.STOCK_EXECUTE)
		self.button_close = Gtk.Button(stock=Gtk.STOCK_CLOSE)

		# Connect the callback functions to the click event
		self.button_dataset.connect("clicked", self.on_button_dataset_clicked)
		self.button_real_partition.connect("clicked", self.on_button_real_partition_clicked, "Real")
		self.button_generated_partition.connect("clicked", self.on_button_generated_partition_clicked, "Generated")
		self.button_similarity.connect("clicked", self.on_button_similarity_clicked)
		self.button_validation.connect("clicked", self.on_button_validation_clicked)
		self.button_execute.connect("clicked", self.on_button_execute_clicked)
		self.button_close.connect("clicked", self.on_button_close_clicked)

		# Associate the buttons to the containers
		self.bbox1.pack_start(self.button_dataset, True, True, 0)
		self.bbox1.pack_start(self.button_real_partition, True, True, 0)
		self.bbox1.pack_start(self.button_generated_partition, True, True, 0)
		self.bbox2.pack_start(self.button_similarity, True, True, 0)
		self.bbox2.pack_start(self.button_validation, True, True, 0)
		self.bbox3.pack_start(self.button_execute, True, True, 0)
		self.bbox3.pack_start(self.button_close, True, True, 0)

		self.win_dataset = DataSetWindow()
		self.win_real_partition = RealPartitionWindow()
		self.win_generated_partition = GeneratedPartitionWindow()
		self.win_validation = ValidationWindow()
		self.win_similarity = SimilarityWindow()

	def on_button_dataset_clicked(self, widget):
		self.win_dataset.show_all()

	def on_button_real_partition_clicked(self, widget, data):
		self.win_real_partition.show_all()

	def on_button_generated_partition_clicked(self, widget, data):
		self.win_generated_partition.show_all()

	def on_button_validation_clicked(self, widget):
		self.win_validation.show_all()
		
	def on_button_similarity_clicked(self, widget):
		self.win_similarity.show_all()

	def on_button_close_clicked(self, widget):
		Gtk.main_quit()

	def on_button_execute_clicked(self, widget):
		# instanciate Clex
		self.clex = Clex()
		
		self.clex.setSimilarity(self.win_similarity.get_similarity())

		# instanciate DataSets
		self.win_dataset_list = self.win_dataset.get_selection_list()
		self.dataset_list = StrPairVector(len(self.win_dataset_list))
		for i in range(0, len(self.dataset_list)):
			# splittng directory from the filename
			self.head, self.tail = path.split(self.win_dataset_list[i][0])
			# cutting 'file://' off and converting unicode to bytecode and creating a pair of strings
			self.dataset_list[i] = StrPair(urlparse(self.head).path.encode() + '/', self.tail.encode())

		self.clex.setDataSet(self.dataset_list)

win = MainWindow()
win.connect("delete-event", Gtk.main_quit)
win.show_all()
Gtk.main()
