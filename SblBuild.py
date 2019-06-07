#!/usr/bin/env python
## @ SblBuild.py
# Slim Bootloader build wrapper script
#
# Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
# This program and the accompanying materials are licensed and made available under
# the terms and conditions of the BSD License that accompanies this distribution.
# The full text of the license may be found at
# http://opensource.org/licenses/bsd-license.php.
#
# THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
##

##
# Import Modules
#
import os
import sys
import subprocess

def main():
	args = sys.argv[1:]
	if len(args) == 0:
		print 'No parameter is given.\nTry "%s -h" to get help' % (os.path.basename(sys.argv[0]))
		return 0

	plt_dir = os.path.dirname (os.path.realpath(__file__))
	os.environ['WORKSPACE']  = plt_dir
	os.environ['PLT_SOURCE'] = os.path.join (plt_dir, 'SblInternal')

	sbl_build_script = os.path.abspath(os.path.join(plt_dir, 'SblOpen', 'BuildLoader.py'))
	build_cmd        = ["python", sbl_build_script]

	build_cmd.extend(args)
	x = subprocess.call(build_cmd)
	if x:
		raise RuntimeError("Execution failed: %s " % (build_cmd))

if __name__ == '__main__':
	sys.exit(main())
