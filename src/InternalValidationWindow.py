from ValidationWindow import *

class InternalValidationWindow(ValidationWindow):
	def __init__(self):
		ValidationWindow.__init__(self, "External")
		self.store.append(["Connectivity"])
		self.store.append(["Deviation"])
		self.store.append(["Silhouette"])
