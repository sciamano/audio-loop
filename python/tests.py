import unittest

import audio_loop as al

class Test1(unittest.TestCase):

    def test01(self):
        self.assertEqual(al.play(), 'playing')

    def test02(self):
        self.assertEqual(len(al.actions()), 3)


if __name__ == '__main__':
    unittest.main()
